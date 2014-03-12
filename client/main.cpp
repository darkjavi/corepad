#include <QApplication>

#include "../common/cclient.h"
#include "cclientview.h"
#include "cchatroomsview.h"
#include "cusersview.h"
#include "cpadview.h"

#include "cmainview.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  cMainView window;

  window.show();

  return app.exec();
}

/*
   This is a model for threaded client/server communication using the Qt QtNetwork class library.

   A threaded server is created that waits for a client connection.  When the client
   connects, the client sends a string (terminated by a \r) to the server.  The server
   reads the string and echos it back to the client.  The client then prints out the string.
*/
/*
//#include "windows.h"
#include "QMutex"
#include "QThread"
#include "QTcpServer"
#include "QTcpSocket"
#include "QVector"
#include "QString"

class SocketThreadBase
{
public:
  SocketThreadBase(const QString &ipAddr, const ushort port ) : mIP( ipAddr ), mPort( port )
  {
    mRunThread = false;
  }
  enum Identity {
    BAD_IDENTITY,
    SERVER,
        CLIENT
  };
  virtual void startThread() = 0;
  virtual void stopThread() = 0;
  virtual Identity getIdentity() = 0;
protected:
  QMutex mMutex;
  const QString mIP;
  const ushort mPort;

  void setRunThread( bool newVal );
  bool getRunThread();
  void run();
  QString readLine(QTcpSocket *socket );
  int waitForInput( QTcpSocket *socket );
  void writeLine( QTcpSocket *client, const QString &line );
private:
  bool mRunThread;
};


class EchoServer : public SocketThreadBase, QThread
{
public:
  EchoServer(const QString &ipAddr, const ushort port ) : SocketThreadBase( ipAddr, port ) {}
  void startThread();
  void stopThread();
  Identity getIdentity() { return SERVER; }
protected:
  void run();
  void echoServer( QTcpSocket *client );
};

class EchoClient : public SocketThreadBase, QThread
{
public:
  EchoClient(const QString &ipAddr, const ushort port ) : SocketThreadBase( ipAddr, port ) { mDone = false; }
  void startThread();
  void stopThread();
  bool isDone();
  Identity getIdentity() { return CLIENT; }
protected:
  void run();
  void setDone( const bool newVal );

private:
  static const unsigned int CONNECT_TIME_OUT = 5 * 1000; // 5 seconds
  static const char *mStrings[];
  static const uint mNumStrings;
  bool mDone;
};



void SocketThreadBase::setRunThread(bool newVal )
{
  QMutexLocker lock( &mMutex );
  mRunThread = newVal;
}

bool SocketThreadBase::getRunThread()
{
  QMutexLocker lock( &mMutex );
  return mRunThread;
}


int SocketThreadBase::waitForInput( QTcpSocket *socket )
{
  int bytesAvail = -1;
  while (socket->state() == QAbstractSocket::ConnectedState && getRunThread() && bytesAvail < 0) {
    if (socket->waitForReadyRead( 100 )) {
      bytesAvail = socket->bytesAvailable();
    }
    else {
      sleep( 50 );
    }
  }
  return bytesAvail;
}

QString SocketThreadBase::readLine(QTcpSocket *socket )
{
  QString line = "";
  int bytesAvail = waitForInput( socket );
  if (bytesAvail > 0) {
    int cnt = 0;
    bool endOfLine = false;
    bool endOfStream = false;
    while (cnt < bytesAvail && (!endOfLine) && (!endOfStream)) {
      char ch;
      int bytesRead = socket->read(&ch, sizeof(ch));
      if (bytesRead == sizeof(ch)) {
    cnt++;
    line.append( ch );
    if (ch == '\r') {
      endOfLine = true;
    }
      }
      else {
    endOfStream = true;
      }
    }
  }
  return line;
}


void SocketThreadBase::writeLine(QTcpSocket *socket, const QString &line)
{
  if (line.length() > 0) {
    socket->write( line.toAscii() );
    if (! socket->waitForBytesWritten()) {
      if (getIdentity() == SERVER) {
    printf("Server - ");
      }
      else if (getIdentity() == CLIENT) {
    printf("Client - ");
      }
      else {
    printf("Unknown identity - ");
      }
      printf("writeLine: the write to the socket failed\n");
    }
  }
}

void EchoServer::echoServer(QTcpSocket *client )
{
  QString line;
  do {
    line = readLine( client );
    if (line.length() > 0) {
      writeLine( client, line );
    }
  } while (line.length() > 0);
}


/*
  Note that Qt requires that the QTcpServer be in the same thread it is used in.
  So it cannot be declared as a class variable.  It must be in the run thread.
*/
/*
void EchoServer::run()
{
  QHostAddress serverAddr( mIP );
  QTcpServer server;
  if (server.listen(serverAddr, mPort)) {
    printf("EchoServer::run: listen() succeeded\n");
    while (server.isListening() && getRunThread()) {
      if (server.waitForNewConnection(100)) {
    printf("EchoServer::run: got a TCP connection\n");
    QTcpSocket *client = server.nextPendingConnection();
    echoServer( client );
      }
      else {
    sleep( 100 );
      }
    } // while
  }
  else {
    printf("EchoServer::run: listen operation failed\n");
  }
}

void EchoServer::startThread()
{
  setRunThread( true );
  start();
}

void EchoServer::stopThread()
{
  setRunThread( false );
}


void EchoClient::setDone(const bool newVal)
{
  QMutexLocker lock( &mMutex );
  mDone = newVal;
}

bool EchoClient::isDone()
{
  QMutexLocker lock( &mMutex );
  return mDone;
}

/*
    Note that the QTcpSocket object must be in the run thread.  It cannot
    be a class variable.
*/
/*
void EchoClient::run()
{
  QTcpSocket socket;
  QHostAddress hostAddr( mIP );
  socket.connectToHost( hostAddr, mPort );
  if (socket.waitForConnected( CONNECT_TIME_OUT )) {
    QHostAddress hostAddr = socket.localAddress();
    QString addr = "";
    if (hostAddr != QHostAddress::Null) {
      addr = hostAddr.toString();
    }
    printf("Client connected");
    if (addr.length() > 0) {
      printf(" on address %s:%04d", addr.toAscii().data(), socket.localPort() );
    }
    printf("\n");
    int ix = 0;
    while (socket.state() == QAbstractSocket::ConnectedState && ix < mNumStrings) {
      QString line( mStrings[ix] );
      writeLine(&socket, line);
      QString echoedLine = readLine( &socket );
      if (echoedLine.length() > 0) {
    if (line != echoedLine) {
      printf("line and echoed line doesn't match\n");
    }
    else {
      printf("%s\n", line.toAscii().data() );
    }
      }
      ix++;
    } // while
  }
  else {
    printf("Client socket failed to connect\n");
  }
  setDone( true );
}


void EchoClient::startThread()
{
  setRunThread( true );
  start();
}

void EchoClient::stopThread()
{
}


const char *EchoClient::mStrings[] = {
  "    'Twas brillig, and the slithy toves\r",
  "        Did gyre and gimble in the wabe:\r",
  "    All mimsy were the borogoves,\r",
  "        And the mome raths outgrabe.\r",
  " \r",
  "    \"Beware the Jabberwock, my son!\r",
  "        The jaws that bite, the claws that catch!\r",
  "    Beware the Jubjub bird, and shun\r",
  "        The frumious Bandersnatch!\"\r",
  " \r",
  "    He took his vorpal sword in hand: \r",
  "        Long time the manxome foe he sought--\r",
  "    So rested he by the Tumtum tree, \r",
  "        And stood awhile in thought. \r",
  " \r",
  "    And, as in uffish thought he stood,\r",
  "        The Jabberwock, with eyes of flame,\r",
  "    Came whiffling through the tulgey wood,\r",
  "        And burbled as it came!\r",
  " \r",
  "    One, two!  One, two!  And through and through\r",
  "        The vorpal blade went snicker-snack!\r",
  "    He left it dead, and with its head\r",
  "        He went galumphing back. \r",
  " \r",
  "    \"And hast thou slain the Jabberwock?\r",
  "        Come to my arm, my beamish boy!\r",
  "    O frabjous day! Callooh!  Callay!\"\r",
  "        He chortled in his joy.\r",
  " \r",
  "    'Twas brillig, and the slithy toves\r",
  "        Did gyre and gimble in the wabe:\r",
  "    All mimsy were the borogoves, \r",
    "        And the mome raths outgrabe\r"
};

const uint EchoClient::mNumStrings = sizeof EchoClient::mStrings / sizeof( *EchoClient::mStrings );



int main(int argc, char *argv[])
{
  const QString IP =     "127.0.0.3";
  const ushort port = 9999;
  EchoServer server(IP, port );
  EchoClient client(IP, port );
  server.startThread();
  client.startThread();
  while (! client.isDone()) {
    sleep( 100 );
  }
  return 0;
}
*/

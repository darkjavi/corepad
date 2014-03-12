#include "cclient.h"

// public methods
cClient::cClient(quint8 client_type)
{
  m_tx_count = 0;
  m_rx_count = 0;
  m_clientType = client_type;
  m_auth = new cClientAuth(&m_channel_parser.channel_user(),client_type);
  m_channel_parser.set_parent_client(this);

  connect(this,SIGNAL(readyRead()),
          this, SLOT(readSocket()));
  connect(&m_channel_parser,SIGNAL(parser_tx(QByteArray)),
          this,SLOT(socket_tx(QByteArray)));

  connect(this,SIGNAL(socket_rx(QByteArray)),
          &m_channel_parser,SLOT(parser_rx(QByteArray)));
  connect(m_auth,SIGNAL(login_status(bool,QString)),this,SLOT(rcv_login_status(bool,QString)));

  if(client_type == cClient::typeServerClient)
  {
      connect(this,SIGNAL(disconnected()),this,SLOT(deleteLater()));
  }
  else
  {
      m_keepAliveT = new QTimer();
      connect(m_keepAliveT,SIGNAL(timeout()),this,SLOT(keep_alive()));
      connect(this,SIGNAL(connected()),this,SLOT(start_login()));
      connect(&m_channel_parser.channel_user(),SIGNAL(user_info(cUser)),this,SLOT(rcv_user_info(cUser)));
  }
//protocolo server:
  connect(&m_channel_parser.channel_server(),SIGNAL(get_client_version()),this,SLOT(get_client_version()));
  connect(&m_channel_parser.channel_server(),SIGNAL(ping()),this,SLOT(ping()));
  connect(&m_channel_parser.channel_server(),SIGNAL(pong()),this,SLOT(pong()));
}

cClient::~cClient()
{
  close();
  if(m_clientType == cClient::typeClient)
  {
      delete m_keepAliveT;
  }
}

void cClient::set_user(cUser user)
{
    m_user = user;
    channel_user().send_user_info(m_user);
}

void cClient::rcv_user_info(cUser user)
{
    m_user = user;
}

QString cClient::info()
{
    QString srt("CLIENT-INFO:\n\n");
    srt.append("\tconnected:\t").append(QString::number(m_uptime.toTime_t()));
    srt.append("\n\tuptime :\t").append(QString::number(m_uptime.secsTo(QDateTime::currentDateTime())));
    srt.append("\n\tusername:\t").append(m_username);
    srt.append("\n\tlast ping:\t").append(QString::number(m_lastPing)).append("ms");
    srt.append("\n\ttx packets:\t").append(QString::number(m_tx_count));
    srt.append("\n\trx packets:\t").append(QString::number(m_rx_count));
    return srt;
}

// private slots
void cClient::readSocket()
{
  emit rx();
  m_rx_count++;
  QByteArray data = this->readAll();
  emit socket_rx(data);
}

void cClient::socket_tx(const QByteArray &data)
{
  emit tx();
  m_tx_count++;
  this->write(data);
}

void cClient::connectSocket(QString host, int port)
{
  this->connectToHost(host,port);
}

void cClient::start_login()
{
    m_auth->login_start(m_username,m_passwd);
}

void cClient::closeSocket()
{
  this->close();
}

void cClient::init(QString user, QString password, QString host, int port)
{
    qDebug() << "[INFO]cClient::init-> conectando:" << user << "@" << host << ":" << port;
    m_username      = user;
    m_passwd    = password;
    this->connectToHost(host,port);
}

void cClient::rcv_login_status(bool status, QString reason)
{
    qDebug() << "[INFO]cClient::rcv_login_status-> login" << status << "-" << reason;
    if(!status)
    {
        if(m_clientType == typeClient)
        {
            m_keepAliveT->stop();
        }
        this->close();
    }
    else
    {
        m_uptime = QDateTime::currentDateTime();
        m_username = m_auth->get_username();
        if(m_clientType == typeClient)
        {
            m_keepAliveT->start(m_keepAliveRate);
            channel_user().send_get_user_info();
        }
        emit login_status(status,reason);
    }
}

void cClient::get_client_version()
{
    cChannelServer* channel = (cChannelServer*)sender();
    channel->send_client_version(get_clientVersion());
}

void cClient::ping()
{//Si recibimos un ping, contestamos con un pong
    cChannelServer* channel = (cChannelServer*)sender();
    channel->send_pong();
}

void cClient::pong()
{
    quint16 elapsed = m_pingMeter.elapsed();
    qDebug() << "[INFO]cClient::pong()-> Ping time:" << elapsed << "ms";
    emit  ping_time(elapsed);
}

void cClient::keep_alive()
{
    m_channel_parser.channel_server().send_ping();
    m_pingMeter.start();
}

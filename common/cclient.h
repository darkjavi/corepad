#ifndef CCLIENT_H
#define CCLIENT_H

#include <QTcpSocket>
#include <QDateTime>
#include <QTimer>

#include "cchannelparser.h"
#include "cclientauth.h"
#include "cuser.h"

#define CLIENT_VERSION      1
#define KEEP_ALIVE_RATE     5000

class cClientAuth;
class cClient : public QTcpSocket
{
  Q_OBJECT

public:
  enum client_type
  {
      typeClient,
      typeServerClient
  };

  cClient(quint8 client_type);
  ~cClient();
  quint16 get_clientVersion()    {return CLIENT_VERSION;}
  const QString& get_userName()  {return m_username;}

  QVector<cContentChannel*>&  channels()          {return m_channel_parser.channels();}
  cChannelServer&             channel_server()    {return m_channel_parser.channel_server();}
  cChannelUser&               channel_user()      {return m_channel_parser.channel_user();}
  cChannelSession&            channel_session()   {return m_channel_parser.channel_session();}
  void          set_user(cUser user);
  cUser&        get_user()      {return m_user;}
  cUserInfo     get_userInfo()  {return m_user.get_userInfo();}
  QString info();
protected:
  quint8                m_clientType;
  cChannelParser        m_channel_parser;
  cClientAuth*          m_auth;
  cUser                 m_user;
  QString               m_username;
  QString               m_passwd;
  QDateTime             m_uptime;
  QTimer*               m_keepAliveT;
  QTime                 m_pingMeter;
  quint16               m_lastPing;
  quint64               m_tx_count;
  quint64               m_rx_count;
  static const quint16  m_keepAliveRate = KEEP_ALIVE_RATE;

  void setUserPassword  (QString user, QString password);
  void connectSocket    (QString host,int port);

  static const quint16  m_version = CLIENT_VERSION;
signals:
  void tx();
  void rx();
  void ping_time(quint16);
  void socket_rx(const QByteArray& data);
  void login_status(bool status,QString reason = "I say so");
  void user_info(cUser user);
private slots:
  void readSocket();
  void socket_tx(const QByteArray& data);
  void rcv_login_status(bool status,QString reason = "I say so");
  void start_login();
  void keep_alive();
  void rcv_user_info(cUser user);

  //protocolo:
  void get_client_version();
  void ping();
  void pong();
public slots:
  void closeSocket();
  void init(QString user, QString password,  QString host, int port);
};

#endif // CCLIENT_H

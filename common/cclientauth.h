#ifndef CCLIENTAUTH_H
#define CCLIENTAUTH_H

#include <QObject>
#include <QTimer>
#include <QString>
#include <QVector>

#include "cclient.h"

class cClientAuth  : public QObject
{
    Q_OBJECT
public:
  cClientAuth(cChannelUser* user_channel,quint8 type, QObject *pParent = 0);
  const QString& get_username(){return m_user;}

private:
  bool check_username(const QString &user, const QString &passwd);
  void connect_channel();
  cChannelUser* m_channel;
  QTimer   m_timer;
  QString  m_user;
  QString  m_passwd;
  quint8   m_type;

signals:
  void login_status(bool status,QString reason = "none");

private slots:
  void auth_timeout();
  void greet();
  void login(const QString& user, const QString& passwd);
  void rcv_login_status(bool status,QString reason = "none");

public slots:
  void login_start(const QString& user, const QString& passwd);
};

#endif // CCLIENTAUTH_H

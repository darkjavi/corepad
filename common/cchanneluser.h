#ifndef CCHANNELUSER_H
#define CCHANNELUSER_H

#include "ccontentchannel.h"
#include "csessioninfo.h"
#include "cuser.h"
class cChannelUser : public cContentChannel
{
    Q_OBJECT
public:
    explicit cChannelUser(QObject *parent = 0);
private:
    enum userCommands
    {
        CMD_GREET,
        CMD_LOGIN,
        CMD_LOGIN_STATUS,
        CMD_GET_USER_DATA,
        CMD_USER_DATA,
        CMD_GET_SESSIONS,
        CMD_SESSIONS_LIST
    };

signals:
    void dataTX(const QVector<QByteArray>& data);
    void login_status(bool status, QString reason = "I said so");
    void login(const QString& user, const QString& passwd);
    void greet();
    void get_user_info();
    void user_info(cUser user);
    void get_sessions();
    void sessions_list(QVector<cSessionInfo>&);
public slots:
    void dataRX(const QVector<QByteArray>& data);
    void send_login_status(bool status, QString reason = "I said so");
    void send_login(const QString& user, const QString& passwd);
    void send_greet();
    void send_get_user_info();
    void send_user_info(cUser user);
    void send_get_sessions();
    void send_sessions_list(QVector<cSessionInfo> sessions);
};

#endif // CCHANNELUSER_H

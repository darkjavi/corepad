#ifndef CCHANNELSERVER_H
#define CCHANNELSERVER_H

#include "ccontentchannel.h"

class cChannelServer : public cContentChannel
{
    Q_OBJECT
public:
    explicit cChannelServer(QObject *parent = 0);
private:
    enum serverCommands
    {
        CMD_PING,
        CMD_PONG,
        CMD_GET_SERVER_VERSION,
        CMD_SERVER_VERSION,
        CMD_GET_CLIENT_VERSION,
        CMD_CLIENT_VERSION,
        CMD_GET_SERVER_NAME,
        CMD_SERVER_NAME,
        CMD_GET_MOTD,
        CMD_MOTD
    };
signals:
    void dataTX(const QVector<QByteArray>& data);
    void ping();
    void pong();
    void get_server_version();
    void server_version(quint16 version);
    void get_client_version();
    void client_version(quint16 version);
    void get_server_name();
    void server_name(QString name);
    void get_motd();
    void motd(QString motd);


public slots:
    void dataRX(const QVector<QByteArray>& data);
    void send_ping();
    void send_pong();
    void send_get_server_version();
    void send_server_version(quint16 version);
    void send_get_client_version();
    void send_client_version(quint16 version);
    void send_get_server_name();
    void send_server_name(QString name);
    void send_get_motd();
    void send_motd(QString motd);

};

#endif // CCHANNELSERVER_H

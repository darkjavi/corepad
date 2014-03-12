#ifndef SSERVER_H
#define SSERVER_H

#include <QObject>
#include <QVector>
#include <QDateTime>

#include "sgate.h"
#include "../common/cclient.h"
#include "susermanager.h"
#include "ssessionmanager.h"

#define SERVER_VERSION  1

class sServer : public QObject
{
    Q_OBJECT
protected:
    QVector<sGate*>     m_gates;
    sUserManager        m_user_manager;
    sSessionManager     m_session_manager;
    QDateTime           m_uptime;
    quint16             m_port;
    static const quint16 m_version = SERVER_VERSION;
public:
    explicit sServer(QObject *parent = 0);
    quint16          get_serverVersion()  {return m_version;}
    QVector<sGate*>& get_gates()          {return m_gates;}

signals:
    void new_client(cClient* n_client);
    void client_list(QList<cClient*>& clients);
    void tx();
    void rx();
private slots:
    //protocolo:
    void get_server_version();
    void ping();
    void pong();
public slots:
    void add_client(cClient* n_client);
    void poweroff() {this->deleteLater();}
};

#endif // SSERVER_H

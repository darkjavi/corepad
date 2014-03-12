#ifndef SGATE_H
#define SGATE_H

#include <QObject>
#include <QtNetwork>

#include "../common/cclient.h"

class sGate : public QTcpServer
{
    Q_OBJECT
public:
    explicit sGate(QObject *parent = 0);
    quint64 get_connectionAttemps() {return m_connection_attemps;}
    quint64 get_connectionSuccess() {return m_connection_success;}
    quint64 get_connectionFailed()  {return m_connection_failed;}
    quint64 get_connectioBadauth()  {return m_connection_badauth;}
    quint64 client_count()          {return m_clients.count();}
private:
    quint64 m_connection_attemps;
    quint64 m_connection_success;
    quint64 m_connection_failed;
    quint64 m_connection_badauth;
protected:
    void incomingConnection(int socketDescriptor);
    QList<cClient*> m_clients;
signals:
    void new_client(cClient* n_client);
    void tx();
    void rx();
private slots:
    void client_auth(bool status,QString reason);
    void remove_client(QObject *obj);
public slots:
    
};

#endif // SGATE_H

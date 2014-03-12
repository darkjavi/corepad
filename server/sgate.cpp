#include "sgate.h"

sGate::sGate(QObject *parent) :
    QTcpServer(parent)
{
    m_connection_attemps = 0;
    m_connection_success = 0;
    m_connection_failed  = 0;
    m_connection_badauth = 0;
}

void sGate::incomingConnection(int socketDescriptor)
{
    m_connection_attemps++;
    cClient *client = new cClient(cClient::typeServerClient);
    qDebug() << "[INFO]sGate::incomingConnection-> incoming:" << socketDescriptor ;
    if (client->setSocketDescriptor(socketDescriptor))
    {
        connect(client,SIGNAL(login_status(bool,QString)),this,SLOT(client_auth(bool,QString)));
    }
    else
    {
        delete client;
        m_connection_failed++;
    }
}

void sGate::client_auth(bool status, QString reason)
{
    cClient* client = qobject_cast<cClient *>(sender());
    if (status)
    {
        m_connection_success++;
        qDebug() << "[INFO]sGate::client_auth-> auth OK! :" << client->get_userName();
        m_clients.append(client);
        connect(client,SIGNAL(destroyed(QObject*)),this,SLOT(remove_client(QObject*)));
        connect(client,SIGNAL(tx()),this,SIGNAL(tx()));
        connect(client,SIGNAL(rx()),this,SIGNAL(rx()));
        emit new_client(client);
    }
    else
    {
        m_connection_badauth++;
        qDebug() << "[INFO]sGate::client_auth-> auth FAILED!" << client->get_userName() << reason;
        delete client;
    }
}

void sGate::remove_client(QObject * obj)
{
    cClient* client = (cClient*) obj;
    m_clients.removeAll(client);
}

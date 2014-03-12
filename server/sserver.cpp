#include "sserver.h"

sServer::sServer(QObject *parent) :
    QObject(parent)
{
    m_port = 31415;

    m_uptime = QDateTime::currentDateTime();
    m_user_manager.set_sesionManager(&m_session_manager);
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0 ; i < ipAddressesList.count() ; i++)
    {
        sGate* gate = new sGate(this);
        if(gate->listen(ipAddressesList.at(i),m_port))
        {
            qDebug() << "[INFO]sServer::sServer-> escuchando:" << gate->serverAddress() << gate->serverPort();
            connect(gate,SIGNAL(new_client(cClient*)),this,SLOT(add_client(cClient*)));
            connect(gate,SIGNAL(new_client(cClient*)),this,SIGNAL(new_client(cClient*)));
            m_gates.append(gate);
        }
        else
        {
            qDebug() << "[WARN]sServer::sServer-> No puedo escuchar en:" << ipAddressesList.at(i).toString() << m_port;
            delete gate;
        }
    }
    if(m_gates.count() == 0)
    {
        qDebug() << "[FATAL]sServer::sServer-> No puedo escuchar en: ninguna ip :(";
        exit(1);
    }
    connect(&m_user_manager,SIGNAL(client_list(QList<cClient*>&)),this,SIGNAL(client_list(QList<cClient*>&)));
    qDebug() << "[INFO]sServer::sServer-> Up & Running :)";

}


void sServer::add_client(cClient *n_client)
{
    connect(n_client,SIGNAL(tx()),this,SIGNAL(tx()));
    connect(n_client,SIGNAL(rx()),this,SIGNAL(rx()));

    connect(&n_client->channel_server(),SIGNAL(get_server_version()),this,SLOT(get_server_version()));
    //connect(&n_client->channel_server(),SIGNAL(ping()),this,SLOT(ping()));
    //connect(&n_client->channel_server(),SIGNAL(pong()),this,SLOT(pong()));

    m_user_manager.add_client(n_client);
}

void sServer::get_server_version()
{
    cChannelServer* channel = (cChannelServer*)sender();
    channel->send_server_version(get_serverVersion());
}

void sServer::ping()
{//Si recibimos un ping, contestamos con un pong
    cChannelServer* channel = (cChannelServer*)sender();
    channel->send_pong();
}

void sServer::pong()
{//

}

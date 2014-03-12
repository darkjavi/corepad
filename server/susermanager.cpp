#include "susermanager.h"

sUserManager::sUserManager(QObject *parent) :
    QObject(parent)
{
    m_session_manager = 0;
}


void sUserManager::connect_client(cClient *client)
{
    connect(client,SIGNAL(destroyed(QObject*)),this,SLOT(remove_client(QObject*)));
    connect(&client->channel_user(),SIGNAL(get_sessions()),this,SLOT(get_sessions()));
    connect(&client->channel_user(),SIGNAL(get_user_info()),this,SLOT(get_user_info()));
    connect(&client->channel_user(),SIGNAL(user_info(cUser)),this,SLOT(user_info(cUser)));
    m_session_manager->connect_client(client);
}

//SLOTS
void sUserManager::add_client(cClient * n_client)
{
    if(m_clients.contains(n_client))
    {
        qDebug() << "[WTF]sUserManager::add_client-> Ein? ya tengo este cliente! : "   << n_client << n_client->get_userName();
        return;
    }
    m_clients.append(n_client);
    connect_client(n_client);
    emit client_list(m_clients);
}

void sUserManager::remove_client(QObject* obj)
{
    cClient* client = (cClient *)obj;
    if(client)
    {
        //qDebug() << "[FIXME]sUserManager::remove_client(QObject* obj)-> No estoy borrando:" << client;
        m_clients.removeAll(client);
        emit client_list(m_clients);
    }
    else
    {
        qDebug() << "[WTF]sServer::remove_client(QObject* obj)-> No puedo borrar:" << client << "Fugados:" << sizeof(cClient) << "Bytes";
    }
}

void sUserManager::get_user_info()
{//mejorar cuando haya base de datos de usuarios....
    cChannelUser* channel = (cChannelUser*)sender();
    cClient* client = channel->get_parent_client();
    QPixmap pix("://img/avatar/tux-robin");
//    QPixmap pix;
//    pix.load("/tmp/img.png","PNG");
    cUser default_user(client->get_userName(),pix);
    qDebug() << "sUserManager::get_user_info()-> pix size:" << pix.size() ;
    client->set_user(default_user);
}

void sUserManager::user_info(cUser user)
{//el usuario manda sus datos actualizados

}

void sUserManager::get_sessions()
{
    QVector<cSessionInfo> data;
    QVector<sContentSession* > sessions = m_session_manager->get_sessions();
    for ( int i = 0 ; i < sessions.count() ; i ++ )
    {
        cSessionInfo session(sessions[i]->get_id(),sessions[i]->get_name());
        data.append(session);
    }
    cChannelUser* client = (cChannelUser*)sender();
    client->send_sessions_list(data);
}

#include "ssessionmanager.h"

sSessionManager::sSessionManager(QObject *parent) :
    QObject(parent)
{
    sContentSession* session = new sContentSession(QString::number(qrand() % 1000),"Main");
    m_sessions.append(session);
    session = new sContentSession(QString::number(qrand() % 1000),"Aux");
    m_sessions.append(session);
}

//SLOTS
void sSessionManager::connect_client(cClient *client)
{
    connect(&client->channel_session(),SIGNAL(join_session(QString)),this,SLOT(join_session(QString)));
}

void sSessionManager::disconnect_client(cClient *client)
{

}

void sSessionManager::join_session(QString id)
{
    for( int i = 0 ; i < m_sessions.count() ; i++ )
    {
        if ( m_sessions[i]->get_id() == id )
        {
            cContentChannel* channel = (cContentChannel*)sender();
            m_sessions[i]->add_client(channel->get_parent_client());
            return;
        }
    }
}

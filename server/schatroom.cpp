#include "schatroom.h"

sChatRoom::sChatRoom(QString id, QString name, bool logging, QObject *parent) :
    QObject(parent)
{
    m_id    = id;
    m_name  = name;
    m_log_enabled = logging;
}

void sChatRoom::add_client(cClient *n_client)
{
    qDebug() << "[DEBUG] Chatroom:" << m_id << "Añadiendo:" << n_client->get_userName();
    if(true)
    {
        if(m_clients.contains(n_client))
        {
            qDebug() << "[DEBUG]sChatRoom::add_client-> already in! : " << n_client->get_userName();
            return;
        }
        n_client->channel_session().send_chatroom_status(m_id,true);
        m_clients.append(n_client);
        connect(n_client,SIGNAL(destroyed(QObject*)),this,SLOT(remove_client(QObject*)));
        connect(&n_client->channel_session(),SIGNAL(chatroom_msg(QString,QVector<cChatMsg>)),this,SLOT(chatroom_msg(QString,QVector<cChatMsg>)));
        connect(this,SIGNAL(send_chatroom_msg(QString,QVector<cChatMsg>)),&n_client->channel_session(),SLOT(send_chatroom_msg(QString,QVector<cChatMsg>)));
        connect(&n_client->channel_session(),SIGNAL(get_chatroom_list(QString)),this,SLOT(get_chatroom_userlist(QString)));
        connect(this,SIGNAL(send_chatroom_userlist(QString,cUsersInfoList)),&n_client->channel_session(),SLOT(send_chatroom_userlist(QString,cUsersInfoList)));
        n_client->channel_session().send_chatroom_msg(m_id,m_history);
        QString str("El Usuario ");
        str.append(n_client->get_userName());
        str.append(" ha entrado en la sala");
        cChatMsg msg("System",str);
        QVector<cChatMsg> msgs;
        msgs.append(msg);
        m_history.append(msg);
        emit send_chatroom_msg(m_id,msgs);
        QVector<cUserInfo> data;
        for( int i = 0 ; i < m_clients.count() ; i++ )
        {
            data.append(m_clients[i]->get_userInfo());
        }
        cUsersInfoList userlist(data);
        emit send_chatroom_userlist(m_id,userlist);
    }
    else
    {
        n_client->channel_session().send_chatroom_status(m_id,false,"Not allowed");
    }
}


void sChatRoom::remove_client(QObject* obj)
{
    cClient* client = (cClient *)obj;
    if(client)
        m_clients.removeAll(client);
    else
        qDebug() << "[WTF]sContentSession::remove_client(QObject* obj)-> No puedo borrar:" << client;

    QString str("El Usuario ");
    str.append(client->get_userName());
    str.append(" ha abandonado la sala");
    cChatMsg msg("System",str);
    QVector<cChatMsg> msgs;
    msgs.append(msg);
    m_history.append(msg);
    emit send_chatroom_msg(m_id,msgs);
}

void sChatRoom::chatroom_msg(QString id, QVector<cChatMsg> msgs)
{
    if(id != m_id)
    {
        return;
    }
    cChannelSession* channel = (cChannelSession*) sender();
    QVector<cChatMsg> ok_msgs;
    for(int i = 0 ; i < msgs.count() ; i++)
    {
        if( msgs[i].get_sender() == channel->get_parent_client()->get_userName())
        {
            ok_msgs.append(msgs[i]);
            m_history.append(msgs[i]);
        }
        else
        {
            qDebug() << "[WTF]sChatRoom::chatroom_msg-> El usuario del mensaje/cliente no coinciden" << channel->get_parent_client()->get_userName() << msgs[i].get_sender();
        }
    }
    if(ok_msgs.count()) emit send_chatroom_msg(m_id,ok_msgs);
}

void sChatRoom::get_chatroom_userlist(QString id)
{
    if(m_id != id)
    {
        return;
    }
    QVector<cUserInfo> data;
    for( int i = 0 ; i < m_clients.count() ; i++ )
    {
        data.append(m_clients[i]->get_userInfo());
    }
    cUsersInfoList userlist(data);
    cChannelSession* channel = (cChannelSession*) sender();
    channel->send_chatroom_userlist(id,userlist);
}

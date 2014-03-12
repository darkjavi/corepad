#include "scontentsession.h"

sContentSession::sContentSession(QString id, QString name, QObject *parent) :
    QObject(parent)
{
    m_name  = name;
    m_id    = id;
//creamos dos salas de chat
    sChatRoom* n_chatr = new sChatRoom(id.append(QString::number(qrand() % 1000)),name.append("Main"),this);
    m_chat_rooms.append(n_chatr);
    n_chatr = new sChatRoom(id.append(QString::number(qrand() % 1000)),name.append("Aux"),this);
    m_chat_rooms.append(n_chatr);
//creamos dos pads
    QString p0 = m_id + QString::number(qrand() % 1000);
    QString p1 = m_id + QString::number(qrand() % 1000);
    sLivePad* pad = new sLivePad(p0,"Main",QPixmap("://img/icons/cplusplus.png"),this);
    m_pads.append(pad);
    pad = new sLivePad(p1,"Aux",QPixmap("://img/icons/cplusplus.png"),this);
    m_pads.append(pad);
}

void sContentSession::add_client(cClient *n_client)
{
    if(true) // comprobacion de acceso a la session
    {
        if(m_clients.contains(n_client))
        {
            qDebug() << "[DEBUG]sContentSession::add_client-> already in! : " << n_client->get_userName();
            return;
        }
        m_clients.append(n_client);
        qDebug() << "[DEBUG]sSessionManager::join_session-> Session:" << m_id << " Añadiendo usuario:" << n_client->get_userName();
        connect(n_client,SIGNAL(destroyed(QObject*)),this,SLOT(remove_client(QObject*)));
        connect(&n_client->channel_session(),SIGNAL(get_chatroom_list(QString)),this,SLOT(get_chatroom_list(QString)));
        connect(&n_client->channel_session(),SIGNAL(join_chatroom(QString)),this,SLOT(join_chatroom(QString)));
        connect(this,SIGNAL(send_chatroom_list(QString,QVector<cChatInfo>&)),&n_client->channel_session(),SLOT(send_chatroom_list(QString,QVector<cChatInfo>&)));
        connect(&n_client->channel_session(),SIGNAL(join_chatroom(QString)),this,SLOT(join_chatroom(QString)));
        connect(&n_client->channel_session(),SIGNAL(get_session_userlist(QString)),this,SLOT(get_session_userlist(QString)));
        connect(this,SIGNAL(send_session_userlist(QString,cUsersInfoList)),&n_client->channel_session(),SLOT(send_session_userlist(QString,cUsersInfoList)));
        connect(&n_client->channel_session(),SIGNAL(get_pad_list(QString)),this,SLOT(get_pad_list(QString)));
        connect(this,SIGNAL(send_pad_list(QString,cPadsInfoList)),&n_client->channel_session(),SLOT(send_pad_list(QString,cPadsInfoList)));
        connect(&n_client->channel_session(),SIGNAL(join_pad(QString)),this,SLOT(join_pad(QString)));
        n_client->channel_session().send_session_status(m_id,true,"SESSION_OK");
    }
    else
    {
        n_client->channel_session().send_session_status(m_id,false,"Not allowed");
    }
}

void sContentSession::remove_client(QObject* obj)
{
    cClient* client = (cClient *)obj;
    if(client)
        m_clients.removeAll(client);
    else
        qDebug() << "[WTF]sContentSession::remove_client(QObject* obj)-> No puedo borrar:" << client;

//    update_user_list();
}

void sContentSession::get_session_userlist(QString id)
{
    cChannelSession* channel = (cChannelSession*) sender();
    QVector<cUserInfo> data;
    for(int i = 0 ; i < m_clients.count() ; i++)
    {
        data.append(m_clients[i]->get_userInfo());
    }
    cUsersInfoList userlist(data);
    channel->send_session_userlist(id,userlist);
}

void sContentSession::get_chatroom_list(QString id)
{
    if(id != m_id) return;
    cChannelSession* channel = (cChannelSession*) sender();
    QVector<cChatInfo> data;
    for (int i = 0 ; i < m_chat_rooms.count() ; i++)
    {
        data.append(m_chat_rooms[i]->get_chatInfo());

    }
    channel->send_chatroom_list(m_id,data);
}

void sContentSession::join_chatroom(QString id)
{
    cChannelSession* channel = (cChannelSession*) sender();
    cClient* client = channel->get_parent_client();
    for (int i = 0 ; i < m_chat_rooms.count() ; i++)
    {
        if(m_chat_rooms[i]->get_id() == id)
        {
            m_chat_rooms[i]->add_client(client);
            return;
        }
    }
    channel->send_chatroom_status(id,false,"Not found!");
}

void sContentSession::get_pad_list(QString id)
{
    if(m_id != id)
    {
        return;
    }
    QVector<cPadInfo> data;
    for(int i = 0 ; i < m_pads.count() ; i++)
    {
        data.append(m_pads[i]->get_padInfo());
    }
    cPadsInfoList padslist(data);
    cChannelSession* channel = (cChannelSession*) sender();
    channel->send_pad_list(m_id,padslist);
}

void sContentSession::join_pad(QString id)
{
    for(int i = 0 ; i < m_pads.count() ; i++)
    {
        if(m_pads[i]->get_id() == id)
        {
            cChannelSession* channel = (cChannelSession*) sender();
            qDebug()<< "SENDER"<<sender();
            m_pads[i]->add_client(channel->get_parent_client());
            return;
        }
    }
}

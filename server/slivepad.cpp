#include "slivepad.h"
#include <QFile>
sLivePad::sLivePad(QString id, QString name, QPixmap icon, QObject *parent) :
    QObject(parent)
{
    m_id   = id;
    m_name = name;
    m_icon = icon;
    QFile demo("://examples/cpp.cpp");
    demo.open(QIODevice::ReadOnly);
    m_doc.setPlainText(demo.readAll());
    m_textCursor = new QTextCursor(&m_doc);//liberar??
}

void sLivePad::add_client(cClient *n_client)
{
    qDebug() << "[INFO]sLivePad::add_client-> añadiendo usuario" << n_client->get_userName();
    if(true)//comprobacion de permisos
    {
        m_clients.append(n_client);
        connect_client(n_client);
        n_client->channel_session().send_pad_status(m_id,true,"Welcome!");
        emit send_pad_userslist(m_id,userslist());
    }
    else
    {
        n_client->channel_session().send_pad_status(m_id,false,"No authorized");
    }
}

cPadInfo sLivePad::get_padInfo()
{
    return(cPadInfo(m_id,m_name,m_icon.scaled(64,64)));
}

void sLivePad::connect_client(cClient *n_client)
{
    connect(n_client,SIGNAL(destroyed(QObject*)),this,SLOT(remove(QObject*)));
    connect(&n_client->channel_session(),SIGNAL(get_pad_userlist(QString)),this,SLOT(get_pad_userslist(QString)));
    connect(this,SIGNAL(send_pad_userslist(QString,cUsersInfoList)),&n_client->channel_session(),SLOT(send_pad_userlist(QString,cUsersInfoList)));
    connect(&n_client->channel_session(),SIGNAL(get_pad_document(QString)),this,SLOT(get_pad_document(QString)));
    connect(this,SIGNAL(send_pad_document(QString,QString&)),&n_client->channel_session(),SLOT(send_pad_document(QString,QString&)));
    connect(&n_client->channel_session(),SIGNAL(pad_changes(QString,QString,int,int,int,QString)),this,SLOT(pad_changes(QString,QString,int,int,int,QString)));
    connect(this,SIGNAL(send_pad_changes(QString,QString,int,int,int,QString)),&n_client->channel_session(),SLOT(send_pad_changes(QString,QString,int,int,int,QString)));
}

void sLivePad::get_pad_userslist(QString id)
{

}

void sLivePad::get_pad_document(QString id)
{
    cChannelSession* channel = (cChannelSession*) sender();
    QString padtext(m_doc.toPlainText());
    channel->send_pad_document(m_id,padtext);
}

void sLivePad::pad_changes(QString id, QString sender, int pos, int del, int add, QString txt)
{
    if(m_id != id)
    {
        return;
    }
    qDebug() << "---------------------" << sender << pos << del << add << txt;
    m_textCursor->setPosition(pos);
    for(int i = 0 ; i < del ; i++)
    {
        m_textCursor->deleteChar();
    }
    if(add)
    {
        m_textCursor->insertText(txt);
    }
    emit send_pad_changes(id,sender,pos,del,add,txt);
}

void sLivePad::remove(QObject *obj)
{
    cClient* client = (cClient*) obj;
    if(!m_clients.removeAll(client))
    {
        qDebug() << "[WTF]sLivePad::remove(QObject *obj)-> No he podido quitar:" << client;
    }
    emit send_pad_userslist(m_id,userslist());
}

cUsersInfoList sLivePad::userslist()
{
    QVector<cUserInfo> data;
    for (int i = 0 ; i < m_clients.count() ; i++)
    {
        data.append(m_clients[i]->get_userInfo());
    }
    cUsersInfoList ulist(data);
    return ulist;
}

#ifndef SCHATROOM_H
#define SCHATROOM_H

#include <QObject>
#include "../common/cclient.h"
#include <../common/cclient.h>
#include <../common/cchatinfo.h>
#include <../common/cchatmsg.h>

class sChatRoom : public QObject
{
    Q_OBJECT
public:
    explicit sChatRoom(QString id, QString name = "default-chat",bool logging = false,QObject *parent = 0);
    void add_client(cClient* n_client);
    QString get_id()    {return m_id;}
    QString get_name()  {return m_name;}

    cChatInfo get_chatInfo()  {return cChatInfo(m_id,m_name,m_clients.count());}
private:
    QList<cClient*>   m_clients;
    QVector<cChatMsg> m_history;
    QString         m_id;
    QString         m_name;
    bool            m_log_enabled;
signals:
    void send_chatroom_msg(QString id, QVector<cChatMsg>);
    void send_chatroom_userlist(QString id,cUsersInfoList userlist);
private slots:
    void get_chatroom_userlist(QString id);
    void chatroom_msg(QString id, QVector<cChatMsg> msgs);

public slots:
    void remove_client(QObject* obj);

};

#endif // SCHATROOM_H

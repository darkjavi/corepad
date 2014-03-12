#ifndef SCONTENTSESSION_H
#define SCONTENTSESSION_H

#include <QObject>
#include <QVector>

#include <../common/cclient.h>
#include <schatroom.h>
#include "slivepad.h"

class sContentSession : public QObject
{
    Q_OBJECT

private:
    QVector<sChatRoom*>  m_chat_rooms;
    QList<cClient*>      m_clients;
    QList<sLivePad*>     m_pads;
    QString              m_id;
    QString              m_name;

    QVector<QString> generate_user_list();

public:
    explicit sContentSession(QString id,QString name = "Default-Session", QObject *parent = 0);
    QString get_name()  {return m_name;}
    QString get_id()    {return m_id;}

signals:
    void send_chatroom_list(QString, QVector<cChatInfo> &chats);
    void send_session_userlist(QString id, cUsersInfoList userlist);
    void send_pad_list(QString id,cPadsInfoList padslist);
private slots:
    void get_chatroom_list(QString id);
    void join_chatroom(QString id);
    void get_session_userlist(QString id);
    void get_pad_list(QString id);
    void join_pad(QString id);
public slots:
    void add_client(cClient* n_client);
    void remove_client(QObject* obj);
};

#endif // SCONTENTSESSION_H

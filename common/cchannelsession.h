#ifndef CCHANNELSESSION_H
#define CCHANNELSESSION_H

#include "cchatmsg.h"
#include "cchatinfo.h"
#include "cfileinfo.h"
#include "cpadsinfolist.h"
#include "cuser.h"
#include "cusersinfolist.h"
#include "ccontentchannel.h"

class cChannelSession : public cContentChannel
{
    Q_OBJECT
public:
    explicit cChannelSession(QObject *parent = 0);
private:
    enum sessionCommands
    {
        CMD_JOIN_SESSION,
        CMD_SESSION_STATUS,
        CMD_GET_SESSION_USERLIST,
        CMD_SESSION_USERLIST,
        CMD_GET_CHATROOM_LIST,
        CMD_CHATROOM_LIST,
        CMD_JOIN_CHATROOM,
        CMD_CHATROOM_STATUS,
        CMD_GET_CHATROOM_USERLIST,
        CMD_CHATROOM_USERLIST,
        CMD_CREATE_CHATROOM,
        CMD_CHATROOM_MSG,
        CMD_GET_FILELIST,
        CMD_FILELIST,
        CMD_GET_PAD_LIST,
        CMD_PAD_LIST,
        CMD_JOIN_PAD,
        CMD_PAD_STATUS,
        CMD_GET_PAD_USERLIST,
        CMD_PAD_USERLIST,
        CMD_GET_PAD_DOCUMENT,
        CMD_PAD_DOCUMENT,
        CMD_PAD_CHANGES
    };

signals:
    void dataTX(const QVector<QByteArray>& data);
    void join_session(QString id);
    void session_status(QString id, bool status, QString Reason);
    void get_session_userlist(QString id);
    void session_userlist(QString id,cUsersInfoList userlist);
    void get_chatroom_list(QString id);
    void chatroom_list(QString id,QVector<cChatInfo>& chats);
    void join_chatroom(QString id);
    void chatroom_status(QString id, bool status,QString reason = "I said so");
    void get_chatroom_userlist(QString chatroom_id);
    void chatroom_userlist(QString chatroom_id, cUsersInfoList userlist);
    void create_chatroom(QString name,bool persistent);
    void chatroom_msg(QString id,QVector<cChatMsg> msg);
    void get_file_list(QString id);
    void file_list(QString id, QVector<cFileInfo>);
    void get_pad_list(QString id);
    void pad_list(QString id,cPadsInfoList padslist);
    void join_pad(QString id);
    void pad_status(QString id, bool status, QString reason = "I said so");
    void get_pad_userlist(QString id);
    void pad_userlist(QString id, cUsersInfoList userlist);
    void get_pad_document(QString id);
    void pad_document(QString id,QString& padText);
    void pad_changes(QString,QString,int,int,int,QString);
public slots:
    void dataRX(const QVector<QByteArray>& data);
    void send_join_session(QString id);
    void send_session_status(QString id, bool status, QString reason);
    void send_get_session_userlist(QString id);
    void send_session_userlist(QString id,cUsersInfoList userlist);
    void send_get_chatroom_list(QString session_id);
    void send_chatroom_list(QString id,QVector<cChatInfo>& chats);
    void send_join_chatroom(QString id);
    void send_chatroom_status(QString id, bool status,QString reason = "I said so");
    void send_get_chatroom_userlist(QString id);
    void send_chatroom_userlist(QString id, cUsersInfoList userlist);
    void send_create_chatroom(QString name,bool persistent);
    void send_chatroom_msg(QString id,QVector<cChatMsg> msgs);
    void send_get_file_list(QString id);
    void send_file_list(QString id, QVector<cFileInfo> files);
    void send_get_pad_list(QString id);
    void send_pad_list(QString id,cPadsInfoList padslist);
    void send_join_pad(QString id);
    void send_pad_status(QString id, bool status, QString reason = "I said so");
    void send_get_pad_userlist(QString id);
    void send_pad_userlist(QString id, cUsersInfoList userlist);
    void send_get_pad_document(QString id);
    void send_pad_document(QString id,QString& padText);
    void send_pad_changes(QString id,QString sender ,int pos, int del, int add, QString txt);
};

#endif // CCHANNELSESSION_H

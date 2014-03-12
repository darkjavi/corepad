#include "cchannelsession.h"

cChannelSession::cChannelSession(QObject *parent) :
    cContentChannel(parent)
{
    m_channel_type = CHANNEL_SESSION;
}

void cChannelSession::dataRX(const QVector<QByteArray> &data)
{
    if (data.count() < 2)
    {
        qDebug() << "[ERROR]cChannelSession::dataRX-> Pocos campos... :" << data.count();
        return;
    }
    int cmd = data[1].toInt();
    //qDebug() << "[INFO]cChannelSession::dataRX-> Comando:" << cmd;
    if(cmd == CMD_JOIN_SESSION)
    {
        QString id = data[2];
        emit join_session(id);
    }
    else if (cmd == CMD_SESSION_STATUS)
    {
        QString id      = data[2];
        bool status     = data[3].toInt();
        QString reason  = data[4];
        emit session_status(id,status,reason);
    }
    else if (cmd == CMD_GET_SESSION_USERLIST)
    {
        QString id = data[2];
        emit get_session_userlist(id);
    }
    else if (cmd == CMD_SESSION_USERLIST)
    {
        QString id = data[2];
        QByteArray array = data[3];
        cUsersInfoList userslist(array);
        emit session_userlist(id,userslist);
    }
    else if (cmd == CMD_GET_CHATROOM_LIST)
    {
        QString id = data[2];
        emit get_chatroom_list(id);
    }
    else if (cmd == CMD_CHATROOM_LIST)
    {
        QString id = data[2];
        QVector<cChatInfo> chats;
        for ( int i = 3 ; i < data.count() ; i+=3 )
        {
            cChatInfo chatroom(data[i],data[i+1],data[i+2].toInt());
            chats.append(chatroom);
        }
        emit chatroom_list(id,chats);
    }
    else if(cmd == CMD_JOIN_CHATROOM)
    {
        QString id = data[2];
        emit join_chatroom(id);
    }
    else if(cmd == CMD_CHATROOM_STATUS)
    {
        QString id      = data[2];
        bool status     = data[3].toInt();
        QString reason  = data[4];
        emit chatroom_status(id,status,reason);
    }
    else if(cmd == CMD_GET_CHATROOM_USERLIST)
    {
        QString chatroom_id = data[2];
        emit get_chatroom_userlist(chatroom_id);
    }
    else if(cmd == CMD_CHATROOM_USERLIST)
    {
        QString id = data[2];
        QByteArray array = data[3];
        cUsersInfoList userslist(array);
        emit chatroom_userlist(id,userslist);
    }
    else if(cmd == CMD_CREATE_CHATROOM)
    {
        QString name    = data[2];
        bool persistent = data[3].toInt();
        emit create_chatroom(name,persistent);
    }
    else if(cmd == CMD_CHATROOM_MSG)
    {
        QVector<cChatMsg> msgs;
        QString id = data[2];
        for ( int i = 3 ; i < data.count() ; i+=3 )
        {
            QDateTime timestamp;
            timestamp.fromMSecsSinceEpoch(data[i+2].toInt());
            cChatMsg msg(data[i],data[i+1],timestamp);
            msgs.append(msg);
        }
        emit chatroom_msg(id,msgs);
    }
    else if(cmd == CMD_GET_FILELIST)
    {
        QString id = data[2];
        emit get_file_list(id);
    }
    else if(cmd == CMD_FILELIST)
    {
        QString id = data[2];

    }
    else if(cmd == CMD_GET_PAD_LIST)
    {
        QString id = data[2];
        emit get_pad_list(id);
    }
    else if(cmd == CMD_PAD_LIST)
    {
        QString id = data[2];
        QByteArray array(data[3]);
        cPadsInfoList padslist(array);
        emit pad_list(id,padslist);

    }
    else if(cmd == CMD_JOIN_PAD)
    {
        QString id = data[2];
        emit join_pad(id);
    }
    else if(cmd == CMD_PAD_STATUS)
    {
        QString id      = data[2];
        bool status     = data[3].toInt();
        QString reason  = data[4];
        emit pad_status(id,status,reason);
    }
    else if(cmd == CMD_GET_PAD_USERLIST)
    {
        QString id = data[2];
        emit get_pad_userlist(id);
    }
    else if(cmd == CMD_PAD_USERLIST)
    {
        QString id = data[2];
        QByteArray array = data[3];
        cUsersInfoList userslist(array);
        emit pad_userlist(id,userslist);
    }
    else if(cmd == CMD_GET_PAD_DOCUMENT)
    {
        QString id(data[2]);
        emit get_pad_document(id);
    }
    else if(cmd == CMD_PAD_DOCUMENT)
    {
        QString id(data[2]);
        QString padText(data[3]);
        emit pad_document(id,padText);
    }
    else if(cmd == CMD_PAD_CHANGES)
    {
        QString id(data[2]);
        QString sender = data[3];
        int pos(data[4].toInt());
        int del(data[5].toInt());
        int add(data[6].toInt());
        QString text(data[7]);
        emit pad_changes(id,sender,pos,del,add,text);
    }
    else
    {
        qDebug() << "[ERROR]cChannelSession::dataRX-> Comando desconocido:" << cmd;
    }
}

void cChannelSession::send_join_session(QString id)
{
    qDebug() << "cChannelSession::send_join_channel";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SESSION));
    QByteArray data1;
    data1.append(QString::number(CMD_JOIN_SESSION));
    QByteArray data2;
    data2.append(id);
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    emit dataTX(data_vector);
}

void cChannelSession::send_session_status(QString id, bool status, QString reason)
{
    qDebug() << "cChannelUser::send_session_status";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SESSION));
    QByteArray data1;
    data1.append(QString::number(CMD_SESSION_STATUS));
    QByteArray data2;
    data2.append(id);
    QByteArray data3;
    data3.append(QString::number(status));
    QByteArray data4;
    data4.append(reason);
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    data_vector.append(data3);
    data_vector.append(data4);
    emit dataTX(data_vector);
}

void cChannelSession::send_get_session_userlist(QString id)
{
    qDebug() << "cChannelSession::send_get_session_userlist";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SESSION));
    QByteArray data1;
    data1.append(QString::number(CMD_GET_SESSION_USERLIST));
    QByteArray data2;
    data2.append(id);
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    emit dataTX(data_vector);
}

void cChannelSession::send_session_userlist(QString id, cUsersInfoList userlist)
{
    qDebug() << "cChannelSession::send_session_userlist";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SESSION));
    QByteArray data1;
    data1.append(QString::number(CMD_SESSION_USERLIST));
    QByteArray data2;
    data2.append(id);
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    data_vector.append(userlist.to_QByteArray());
    emit dataTX(data_vector);
}

void cChannelSession::send_get_chatroom_list(QString session_id)
{
    qDebug() << "cChannelSession::send_get_chatroom_list";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SESSION));
    QByteArray data1;
    data1.append(QString::number(CMD_GET_CHATROOM_LIST));
    QByteArray data2;
    data2.append(session_id);
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    emit dataTX(data_vector);
}

void cChannelSession::send_chatroom_list(QString id, QVector<cChatInfo>& chats)
{
    qDebug() << "cChannelSession::send_chatroom_list";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SESSION));
    QByteArray data1;
    data1.append(QString::number(CMD_CHATROOM_LIST));
    QByteArray data2;
    data2.append(id);
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    for (int i = 0 ; i < chats.count() ; i++)
    {
        QByteArray d0,d1,d2;
        d0.append(chats[i].get_id());
        d1.append(chats[i].get_name());
        d2.append(QString::number(chats[i].get_usercount()));
        data_vector << d0 << d1 << d2;
    }
    emit dataTX(data_vector);
}

void cChannelSession::send_join_chatroom(QString id)
{
    qDebug() << "cChannelSession::send_join_chatroom";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SESSION));
    QByteArray data1;
    data1.append(QString::number(CMD_JOIN_CHATROOM));
    QByteArray data2;
    data2.append(id);
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    emit dataTX(data_vector);
}

void cChannelSession::send_chatroom_status(QString id, bool status,QString reason)
{
    qDebug() << "cChannelUser::send_chatroom_status";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SESSION));
    QByteArray data1;
    data1.append(QString::number(CMD_CHATROOM_STATUS));
    QByteArray data2;
    data2.append(id);
    QByteArray data3;
    data3.append(QString::number(status));
    QByteArray data4;
    data4.append(reason);
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    data_vector.append(data3);
    data_vector.append(data4);
    emit dataTX(data_vector);
}

void cChannelSession::send_get_chatroom_userlist(QString id)
{
    qDebug() << "cChannelSession::send_get_chatroom_userlist";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SESSION));
    QByteArray data1;
    data1.append(QString::number(CMD_GET_CHATROOM_USERLIST));
    QByteArray data2;
    data2.append(id);
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    emit dataTX(data_vector);
}

void cChannelSession::send_chatroom_userlist(QString id, cUsersInfoList userlist)
{
    qDebug() << "cChannelSession::send_join_channel";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SESSION));
    QByteArray data1;
    data1.append(QString::number(CMD_CHATROOM_USERLIST));
    QByteArray data2;
    data2.append(id);
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    data_vector.append(userlist.to_QByteArray());
    emit dataTX(data_vector);
}

void cChannelSession::send_create_chatroom(QString name,bool persistent)
{
    qDebug() << "cChannelUser::send_chatroom_status";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SESSION));
    QByteArray data1;
    data1.append(QString::number(CMD_CREATE_CHATROOM));
    QByteArray data2;
    data2.append(name);
    QByteArray data3;
    data3.append(QString::number(persistent));
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    data_vector.append(data3);
    emit dataTX(data_vector);
}

void cChannelSession::send_chatroom_msg(QString id, QVector<cChatMsg> msgs)
{
    qDebug() << "cChannelSession::send_chatroom_msg";
    QVector<QByteArray> data_vector;
    QByteArray channel;
    channel.append(QString::number(cContentChannel::CHANNEL_SESSION));
    QByteArray command;
    command.append(QString::number(CMD_CHATROOM_MSG));
    QByteArray d_id;
    d_id.append(id);
    data_vector.append(channel);
    data_vector.append(command);
    data_vector.append(d_id);
    for (int i = 0 ; i < msgs.count() ; i++)
    {
        QByteArray d0,d1,d2;
        d0.append(msgs[i].get_sender());
        d1.append(msgs[i].get_message());
        d2.append(QString::number(msgs[i].get_timestamp().toMSecsSinceEpoch()));
        data_vector << d0 << d1 << d2;
    }
    emit dataTX(data_vector);
}

void cChannelSession::send_get_file_list(QString id)
{
    qDebug() << "cChannelSession::send_get_file_list";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SESSION));
    QByteArray data1;
    data1.append(QString::number(CMD_GET_FILELIST));
    QByteArray data2;
    data2.append(id);
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    emit dataTX(data_vector);
}

void cChannelSession::send_file_list(QString id, QVector<cFileInfo> files)
{
    qDebug() << "cChannelSession::send_file_list";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SESSION));
    QByteArray data1;
    data1.append(QString::number(CMD_FILELIST));
    QByteArray data2;
    data2.append(id);
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
//......................
    emit dataTX(data_vector);
}

void cChannelSession::send_get_pad_list(QString id)
{
    qDebug() << "cChannelSession::send_get_pad_list";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SESSION));
    QByteArray data1;
    data1.append(QString::number(CMD_GET_PAD_LIST));
    QByteArray data2;
    data2.append(id);
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    emit dataTX(data_vector);
}

void cChannelSession::send_pad_list(QString id, cPadsInfoList padslist)
{
    qDebug() << "cChannelSession::send_pad_list";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SESSION));
    QByteArray data1;
    data1.append(QString::number(CMD_PAD_LIST));
    QByteArray data2;
    data2.append(id);
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    data_vector.append(padslist.to_QByteArray());
    emit dataTX(data_vector);
}

void cChannelSession::send_join_pad(QString id)
{
    qDebug() << "cChannelSession::send_join_pad";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SESSION));
    QByteArray data1;
    data1.append(QString::number(CMD_JOIN_PAD));
    QByteArray data2;
    data2.append(id);
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    emit dataTX(data_vector);
}

void cChannelSession::send_pad_status(QString id, bool status, QString reason)
{
    qDebug() << "cChannelUser::send_chatroom_status";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SESSION));
    QByteArray data1;
    data1.append(QString::number(CMD_PAD_STATUS));
    QByteArray data2;
    data2.append(id);
    QByteArray data3;
    data3.append(QString::number(status));
    QByteArray data4;
    data4.append(reason);
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    data_vector.append(data3);
    data_vector.append(data4);
    emit dataTX(data_vector);
}

void cChannelSession::send_get_pad_userlist(QString id)
{
    qDebug() << "cChannelSession::send_get_pad_userlist";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SESSION));
    QByteArray data1;
    data1.append(QString::number(CMD_GET_PAD_USERLIST));
    QByteArray data2;
    data2.append(id);
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    emit dataTX(data_vector);
}

void cChannelSession::send_pad_userlist(QString id, cUsersInfoList userlist)
{
    qDebug() << "cChannelSession::send_pad_userlist";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SESSION));
    QByteArray data1;
    data1.append(QString::number(CMD_PAD_USERLIST));
    QByteArray data2;
    data2.append(id);
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    data_vector.append(userlist.to_QByteArray());
    emit dataTX(data_vector);
}

void cChannelSession::send_get_pad_document(QString id)
{
    qDebug() << "send_get_pad_document";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SESSION));
    QByteArray data1;
    data1.append(QString::number(CMD_GET_PAD_DOCUMENT));
    QByteArray data2;
    data2.append(id);
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    emit dataTX(data_vector);
}

void cChannelSession::send_pad_document(QString id, QString &padText)
{
    qDebug() << "send_pad_document";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SESSION));
    QByteArray data1;
    data1.append(QString::number(CMD_PAD_DOCUMENT));
    QByteArray data2;
    data2.append(id);
    QByteArray data3;
    data3.append(padText);
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    data_vector.append(data3);
    emit dataTX(data_vector);
}

void cChannelSession::send_pad_changes(QString id,QString sender,int pos, int del, int add, QString txt)
{
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SESSION));
    QByteArray data1;
    data1.append(QString::number(CMD_PAD_CHANGES));
    QByteArray data2;
    data2.append(id);
    QByteArray data3;
    data3.append(sender);
    QByteArray data4;
    data4.append(QString::number(pos));
    QByteArray data5;
    data5.append(QString::number(del));
    QByteArray data6;
    data6.append(QString::number(add));
    QByteArray data7;
    data7.append(txt);
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    data_vector.append(data3);
    data_vector.append(data4);
    data_vector.append(data5);
    data_vector.append(data6);
    data_vector.append(data7);
    emit dataTX(data_vector);
}

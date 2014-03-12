#include "cchanneluser.h"
#include <QDebug>
#include <QBuffer>

cChannelUser::cChannelUser(QObject *parent) :
    cContentChannel(parent)
{
    m_channel_type = CHANNEL_USER;
}

void cChannelUser::dataRX(const QVector<QByteArray> &data)
{
    if (data.count() < 2)
    {
        qDebug() << "[ERROR]cChannelUser::dataRX-> Pocos campos... :" << data.count();
        return;
    }
    int cmd = data[1].toInt();
    //qDebug() << "[INFO]cChannelUser::dataRX-> Comando:" << cmd;
    if       (cmd == CMD_GREET)
    {
        emit greet();
    }
    else if (cmd == CMD_LOGIN)
    {
        QString user  = data[2];
        QString paswd = data[3];
        emit login(user,paswd);
    }
    else if (cmd == CMD_LOGIN_STATUS)
    {
        bool status     = data[2].toInt();
        QString reason  = data[3];
        emit login_status(status,reason);
    }
    else if (cmd == CMD_GET_USER_DATA)
    {
        emit get_user_info();
    }
    else if (cmd == CMD_USER_DATA)
    {
        QString username = data[2];
        QPixmap pixmap;
        QByteArray bytes = data[3];
        pixmap.loadFromData(bytes, "PNG");
        cUser user(username,pixmap);
        emit user_info(user);
    }
    else if (cmd == CMD_GET_SESSIONS)
    {
        emit get_sessions();
    }else if (cmd == CMD_SESSIONS_LIST)
    {
        QVector<cSessionInfo> sessions;
        for ( int i = 2 ; i < data.count() ; i+=2 )
        {
            cSessionInfo session(data[i],data[i+1]);
            sessions.append(session);
        }
        emit sessions_list(sessions);
    }else
    {
        qDebug() << "[ERROR]cChannelUser::dataRX-> Comando desconocido:" << cmd;
    }
}

void cChannelUser::send_login_status(bool status, QString reason)
{
    qDebug() << "cChannelUser::send_login_status";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_USER));
    QByteArray data1;
    data1.append(QString::number(CMD_LOGIN_STATUS));
    QByteArray data2;
    data2.append(QString::number(status));
    QByteArray data3;
    data3.append(reason);
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    data_vector.append(data3);
    emit dataTX(data_vector);
}

void cChannelUser::send_login(const QString& user, const QString& passwd)
{
    qDebug() << "cChannelUser::send_login";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_USER));
    QByteArray data1;
    data1.append(QString::number(CMD_LOGIN));
    QByteArray data2;
    data2.append(user);
    QByteArray data3;
    data3.append(passwd);
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    data_vector.append(data3);
    emit dataTX(data_vector);
}

void cChannelUser::send_greet()
{
    qDebug() << "cChannelUser::send_greet()";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_USER));
    QByteArray data1;
    data1.append(QString::number(CMD_GREET));
    data_vector.append(data0);
    data_vector.append(data1);
    emit dataTX(data_vector);
}

void cChannelUser::send_get_user_info()
{
    qDebug() << "cChannelUser::send_get_user_info()";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_USER));
    QByteArray data1;
    data1.append(QString::number(CMD_GET_USER_DATA));
    data_vector.append(data0);
    data_vector.append(data1);
    emit dataTX(data_vector);
}

void cChannelUser::send_user_info(cUser user)
{
    qDebug() << "cChannelUser::send_user_info()";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_USER));
    QByteArray data1;
    data1.append(QString::number(CMD_USER_DATA));
    data_vector.append(data0);
    data_vector.append(data1);
    QByteArray data2;
    data2.append(user.get_userName());
    data_vector.append(data2);

    QByteArray bArray;
    QBuffer buffer( &bArray );
    buffer.open( QIODevice::WriteOnly );
    user.get_avatar().save(&buffer, "PNG");
    qDebug() << "[INFO]cChannelUser::send_user_info-> pix_array_size:" << bArray.count() ;
    data_vector.append(bArray);
    emit dataTX(data_vector);
}

void cChannelUser::send_get_sessions()
{
    qDebug() << "cChannelUser::send_get()";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_USER));
    QByteArray data1;
    data1.append(QString::number(CMD_GET_SESSIONS));
    data_vector.append(data0);
    data_vector.append(data1);

    emit dataTX(data_vector);
}

void cChannelUser::send_sessions_list(QVector<cSessionInfo> sessions)
{
    qDebug() << "cChannelUser::send_sessions_list";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_USER));
    QByteArray data1;
    data1.append(QString::number(CMD_SESSIONS_LIST));

    data_vector.append(data0);
    data_vector.append(data1);
    for ( int i = 0 ; i < sessions.count() ; i++ )
    {
        QByteArray data_id(sessions[i].getID().toUtf8());
        data_vector.append(data_id);
        QByteArray data_name(sessions[i].getName().toUtf8());
        data_vector.append(data_name);
    }
    emit dataTX(data_vector);
}

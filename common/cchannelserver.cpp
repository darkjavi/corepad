#include "cchannelserver.h"

cChannelServer::cChannelServer(QObject *parent) :
    cContentChannel(parent)
{
    m_channel_type = CHANNEL_SERVER;
}

void cChannelServer::dataRX(const QVector<QByteArray> &data)
{
    if (data.count() < 2)
    {
        qDebug() << "[ERROR]cChannelServer::dataRX-> Pocos campos... :" << data.count();
        return;
    }
    int cmd = data[1].toInt();
    //qDebug() << "[INFO]cChannelServer::dataRX-> Comando:" << cmd;

    if (cmd==CMD_PING)                  emit ping();
    else if(cmd==CMD_PONG)              emit pong();
    else if(cmd==CMD_GET_SERVER_VERSION)emit get_server_version();
    else if(cmd==CMD_SERVER_VERSION)
    {
        quint16 version = data[2].toInt();
        emit server_version(version);
    }
    else if(cmd==CMD_GET_CLIENT_VERSION)emit get_client_version();
    else if(cmd==CMD_CLIENT_VERSION)
    {
        quint16 version = data[2].toInt();
        emit client_version(version);
    }
    else if(cmd==CMD_GET_SERVER_NAME)   emit get_server_name();
    else if(cmd==CMD_SERVER_NAME)
    {
        QString name = data[2];
        emit server_name(name);
    }
    else if(CMD_GET_MOTD)               emit get_motd();
    else if(cmd==CMD_MOTD)
    {
        QString motd_str = data[2];
        emit motd(motd_str);
    }
    else qDebug() << "[ERROR]cChannelServer::dataRX-> Comando desconocido:" << cmd;
}

void cChannelServer::send_ping()
{
    //qDebug() << "cChannelServer::send_ping";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SERVER));
    QByteArray data1;
    data1.append(QString::number(CMD_PING));
    data_vector.append(data0);
    data_vector.append(data1);
    emit dataTX(data_vector);
}

void cChannelServer::send_pong()
{
    //qDebug() << "cChannelServer::send_pong";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SERVER));
    QByteArray data1;
    data1.append(QString::number(CMD_PONG));
    data_vector.append(data0);
    data_vector.append(data1);
    emit dataTX(data_vector);
}

void cChannelServer::send_get_server_version()
{
    qDebug() << "cChannelServer::send_get_server_version";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SERVER));
    QByteArray data1;
    data1.append(QString::number(CMD_GET_SERVER_VERSION));
    data_vector.append(data0);
    data_vector.append(data1);
    emit dataTX(data_vector);
}

void cChannelServer::send_server_version(quint16 version)
{
    qDebug() << "cChannelServer::send_server_version";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SERVER));
    QByteArray data1;
    data1.append(QString::number(CMD_GET_SERVER_VERSION));
    QByteArray data2;
    data2.append(QString::number(version));
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    emit dataTX(data_vector);
}

void cChannelServer::send_get_client_version()
{
    qDebug() << "cChannelServer::send_get_server_version";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SERVER));
    QByteArray data1;
    data1.append(QString::number(CMD_GET_CLIENT_VERSION));
    data_vector.append(data0);
    data_vector.append(data1);
    emit dataTX(data_vector);
}

void cChannelServer::send_client_version(quint16 version)
{
    qDebug() << "cChannelServer::send_client_version";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SERVER));
    QByteArray data1;
    data1.append(QString::number(CMD_GET_CLIENT_VERSION));
    QByteArray data2;
    data2.append(QString::number(version));
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    emit dataTX(data_vector);
}

void cChannelServer::send_get_server_name()
{
    qDebug() << "cChannelServer::send_get_server_version";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SERVER));
    QByteArray data1;
    data1.append(QString::number(CMD_GET_SERVER_NAME));
    data_vector.append(data0);
    data_vector.append(data1);
    emit dataTX(data_vector);
}

void cChannelServer::send_server_name(QString name)
{
    qDebug() << "cChannelServer::send_server_name";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SERVER));
    QByteArray data1;
    data1.append(QString::number(CMD_GET_SERVER_NAME));
    QByteArray data2;
    data2.append(name);
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    emit dataTX(data_vector);
}

void cChannelServer::send_get_motd()
{
    qDebug() << "cChannelServer::send_get_server_version";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SERVER));
    QByteArray data1;
    data1.append(QString::number(CMD_GET_MOTD));
    data_vector.append(data0);
    data_vector.append(data1);
    emit dataTX(data_vector);
}

void cChannelServer::send_motd(QString motd)
{
    qDebug() << "cChannelServer::send_motd";
    QVector<QByteArray> data_vector;
    QByteArray data0;
    data0.append(QString::number(cContentChannel::CHANNEL_SERVER));
    QByteArray data1;
    data1.append(QString::number(CMD_GET_SERVER_VERSION));
    QByteArray data2;
    data2.append(motd);
    data_vector.append(data0);
    data_vector.append(data1);
    data_vector.append(data2);
    emit dataTX(data_vector);
}

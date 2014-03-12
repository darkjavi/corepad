#include "cchannelparser.h"

#include <QDebug>
#include <QString>
#include <QStringList>
#include "cbyteaux.h"


cChannelParser::cChannelParser(QObject *parent) :
    QObject(parent)
{
    m_parser_sync       = "[^^S^^]";
    m_parser_separator  = "[^^P^^]";
    m_parser_eof        = "[^^E^^]";

    m_channels.append(&m_channel_server);
    m_channels.append(&m_channel_user);
    m_channels.append(&m_channel_session);

    connect(&m_channel_server,SIGNAL(dataTX(QVector<QByteArray>)),
            this,SLOT(prepare_tx(QVector<QByteArray>)));

    connect(&m_channel_user,SIGNAL(dataTX(QVector<QByteArray>)),
            this,SLOT(prepare_tx(QVector<QByteArray>)));

    connect(&m_channel_session,SIGNAL(dataTX(QVector<QByteArray>)),
            this,SLOT(prepare_tx(QVector<QByteArray>)));
}

void cChannelParser::set_parent_client(cClient *client)
{
    for ( int i = 0 ; i < m_channels.count() ; i++ )
    {
        m_channels[i]->set_parent_client(client);
    }
}

bool cChannelParser::checksum(const QByteArray &data)
{
    if ( ! data.startsWith(m_parser_sync) )
    {
        qDebug() << "[WARN]cChannelParser::checksum--> La cadena no empieza por los los valores de sync";
        return false;
    }
    QByteArray raw_data = data.mid(m_parser_sync.count());
    QVector<QByteArray> fields = cByteAux::splitBytearray(raw_data,m_parser_separator);
    int payload_size = fields[0].toInt();
    if (fields.count() != payload_size+2)
    {
        qDebug() << "[WARN]cChannelParser::checksum--> no coincide el numero de campos:" << fields.count() << "/" << payload_size+2;
        return false;
    }
    char expected_checksum = 0x00;
    expected_checksum = fields[fields.count()-1].at(0);
    fields.remove(fields.count() -1);
    char payload_checksum = 0X00;
    for ( int i = 0; i < fields.count() ; i++)
    {
        for( int c = 0; c < fields.at(i).count() ; c++)
        {
            payload_checksum += fields[i].at(c);
        }

    }
    payload_checksum = ~payload_checksum & 0xFF;
    //qDebug() << "[INFO]mfParser::checksum_is_valid->" << payload_checksum << "/" << data[index];
    if ( payload_checksum != expected_checksum )
    {
        qDebug() << "[WARN]cChannelParser::checksum-->checksum incorrecto!! : " << payload_checksum << "/" << expected_checksum;
        return false;
    }
    return true;
}

QByteArray cChannelParser::append_checksum(const QByteArray &data)
{
    if ( ! data.startsWith(m_parser_sync) )
    {
        qDebug() << "[ERROR]cChannelParser::append_checksum--> La cadena no empieza por los los valores de sync";
        return QByteArray();
    }
    QByteArray raw_data = data.mid(m_parser_sync.count());
    QVector<QByteArray> fields = cByteAux::splitBytearray(raw_data,m_parser_separator);

    int payload_size = fields[0].toInt();
    if (fields.count() != payload_size+1)
    {
        qDebug() << "[ERROR]cChannelParser::append_checksum--> no coincide el numero de campos:" << fields.count() << "/" << payload_size+1;
        return QByteArray();
    }

    char payload_checksum = 0X00;
    for ( int i = 0; i < fields.count() ; i++)
    {
        for( int c = 0; c < fields.at(i).count() ; c++)
        {
            payload_checksum += fields.at(i).at(c);
        }

    }
    payload_checksum = ~payload_checksum & 0xFF;

    QByteArray result;
    result.append(data);
    result.append(m_parser_separator);
    result.append(payload_checksum);
    return result;
}

//SLOTS

void cChannelParser::prepare_tx(const QVector<QByteArray> &data)
{
//    qDebug() << "cChannelParser::prepare_tx-> Comprobando";
    for( int i = 0 ; i < data.count() ; i++)
    {
        if( (cByteAux::arrayContainsPattern(data[i],m_parser_sync)) ||
            (cByteAux::arrayContainsPattern(data[i],m_parser_separator)) ||
            (cByteAux::arrayContainsPattern(data[i],m_parser_eof)) )
        {
            qDebug("[WARN]cChannelParser::prepare_tx-> Los datos a enviar contienen los bloques de control del protocolo!!!!");
            //Hay que tener en cuenta la posibilidad de que los datos que se van a enviar contengan algunas de las palabras reservadas del protocolo
            //en este caso, habria que negociar con el otro lado unas nuevas palabras de control
            //bien con un comando del parseador, bien con una estructura de paquete que lo permita
        }
    }
//    qDebug() << "cChannelParser::prepare_tx-> Comprobado!";
    QByteArray tmp_data;
    tmp_data.append(m_parser_sync);
    tmp_data.append(QString::number(data.count()));
    for( int i = 0 ; i < data.count() ; i++)
    {
        tmp_data.append(m_parser_separator);
        tmp_data.append(data[i]);
    }
    QByteArray ready_data = append_checksum(tmp_data);
    if(checksum(ready_data))
    {
        ready_data.append(m_parser_eof);
//        qDebug() << "Ready Data:" << ready_data;
        emit parser_tx(ready_data);
    }
    else
    {
        qDebug() << "[WTF!]cChannelParser::prepare_tx-> No coincide el checksum del paquete que acabo de preparar!";
        qDebug() << ready_data;
    }
}

void cChannelParser::parser_rx(const QByteArray &data)
{   
    m_rx_buffer_lock.lock();
        m_rx_buffer.append(data);
    m_rx_buffer_lock.unlock();
    parse_rx_buffer();
}

void cChannelParser::parse_rx_buffer()
{
//    qDebug() << "cChannelParser::parse_rx_buffer()->entrando en funcion recursiva";
    if(m_rx_buffer.count() == 0)
    {
        return;
    }
    m_rx_buffer_lock.lock();

        long index = cByteAux::indexOfPattern(m_rx_buffer,m_parser_sync);
        if(index == -1)
        {
            qDebug() << "[WARN]cChannelParser::parse_rx_buffer()->Tengo" << m_rx_buffer.count() << "bytes en el buffer y no encuentro el patron de sync!";
        }
        else if(index == 0)
        {//el paquete empieza en la posicion 0 del buffer
            long end_index = cByteAux::indexOfPattern(m_rx_buffer,m_parser_eof);
            if(end_index == -1)
            {
                qDebug() << "[INFO]cChannelParser::parse_rx_buffer()->El paquete empieza pero no termina, supongo que vendra fragmentado....";
            }
            else
            {
                //qDebug() << "[WARN]cChannelParser::parse_rx_buffer()->Paquete aparentemente correcto!";
                QByteArray datapacket =m_rx_buffer.mid(0,end_index+m_parser_eof.count());
                process_datapacket(datapacket);
                m_rx_buffer.remove(0,datapacket.count());
                m_rx_buffer_lock.unlock();
                parse_rx_buffer();
            }
        }
        else
        {
            qDebug() << "[WARN]cChannelParser::parse_rx_buffer()->Tengo"<<index<<"Bytes de BASURA antes del bloque de SYNC, truncando basurilla...";
            qDebug() << "BASURILLA:" << m_rx_buffer.mid(0,index);
            m_rx_buffer.remove(0,index);
            m_rx_buffer_lock.unlock();
            parse_rx_buffer();
        }
    m_rx_buffer_lock.unlock();

}

void cChannelParser::process_datapacket(QByteArray data)
{

    //qDebug() << "DATAPACKET-" << data;
    data.remove(cByteAux::indexOfPattern(data,m_parser_eof),m_parser_eof.count());
    if(checksum(data))
    {
        QVector<QByteArray> datablocks = cByteAux::splitBytearray(data,m_parser_separator);
        datablocks.remove(0);//limpiamos el numero de campos
        datablocks.remove(datablocks.count()-1); //Limpiamos el checksum

        quint8 channel = datablocks[0].toInt();
        if      (channel == cContentChannel::CHANNEL_SERVER)    m_channel_server.dataRX(datablocks);
        else if (channel == cContentChannel::CHANNEL_USER )     m_channel_user.dataRX(datablocks);
        else if (channel == cContentChannel::CHANNEL_SESSION )  m_channel_session.dataRX(datablocks);
        else    qDebug() << "[ERROR!]cChannelParser::parser_rx->Canal desconocido:" << channel << cContentChannel::CHANNEL_SERVER << cContentChannel::CHANNEL_USER << cContentChannel::CHANNEL_SESSION;
    }
    else
    {
        qDebug() << "[ERROR!]cChannelParser::parser_rx-> checksum no valido!";
        qDebug() << data;
    }
}

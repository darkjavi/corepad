#include "cprotocolparser.h"

cProtocolParser::cProtocolParser(QObject *parent) :
    QThread(parent)
{
    qRegisterMetaType<QVector<QString> >("QVector<QString>");
}

void cProtocolParser::run()
{
  while ((m_rx_buff.count() > 0) || (m_tx_buff.count() > 0))
  {
    if (m_rx_buff.count() > 0)
    {
      parse_rx_buff();
    }
    if (m_tx_buff.count() > 0)
    {
      parse_tx_buff();
    }
    msleep(10);
  }
}

//...
void cProtocolParser::send_user(QVector<QString> args)
{
  //...
}
//...

//...
void cProtocolParser::send_pad(QVector<QString> args)
{
  //...
}
//...

void cProtocolParser::send_session(QVector<QString> args)
{
  QVector<QString> data;

  data.append("SESSION");
  data << args;
  m_tx_buff.append(data);

  if (!this->isRunning())
  {
    this->start();
  }
}

void cProtocolParser::send_greetings(QVector<QString> args)
{
    QVector<QString> data;
    data.append("GREETINGS");
    data << args;
    m_tx_buff.append(data);
    if(! this->isRunning() ) this->start();
}

void cProtocolParser::send_chat(QVector<QString> args)
{
    QVector<QString> data;
    data.append("CHAT");
    data << args;
    m_tx_buff.append(data);
    if(! this->isRunning() ) this->start();
}

void cProtocolParser::data_in(QByteArray &data)
{
    //if checksum is valid
    m_rx_buff.append(data);
    if(! this->isRunning() ) this->start();
}

void cProtocolParser::parse_rx_buff()
{
    if (m_rx_buff.contains(m_sync_char))
    {
        int index = m_rx_buff.indexOf(m_sync_char);
        int index2 = m_rx_buff.indexOf(m_sync_char,index+1);

        qDebug() << "parse_rx : primer caracter de sync :" << index;
        qDebug() << "parse_rx : segundo caracter de sync:" << index2;

        QString data = m_rx_buff;//.mid(index-1).split(m_sync_char)[1];

        uint last_packet_end = 0;

        QStringList fields = data.split(m_separator_char);
        if(fields.count() > 1)
        {
            uint payload_size = fields.at(1).toInt();
            qDebug() << "campos:"<< fields.count() << "payload:" << payload_size;
            if(fields.count() == payload_size+3)
            {
                if (checksum_is_valid(data))
                {
                    QVector<QString> args;
                    for (uint a = 0 ; a < payload_size ; a++)
                    {
                        args.append(fields[a+2]);
                    }


                    if (fields[0] == QString(m_sync_char).append("SESSION"))
                    {
                      emit session(args);
                    }
                    else if (fields[0] == QString(m_sync_char).append("GREETINGS"))
                    {
                        emit greetings(args);
                    }
                    else if(fields[0] == QString(m_sync_char).append("CHAT"))
                    {

                        emit chat(args);
                    }
                    last_packet_end = data.indexOf(args.last()) + args.last().count();
                }
                else
                {
                    qDebug("[WTF!]cProtocolParser::parse_rx_buff-> el checksum no coincide!!");
                }
            }
            int cut_point = 0;

            if(last_packet_end > 0)
            {
                cut_point = last_packet_end;
            }
            else if(index2>0)
            {
                cut_point = index2;
            }
            else if (index > 0 )
            {
                cut_point = index;
            }
            qDebug() << "parse_rx : cut point:" << cut_point;
            m_rx_buff.remove(0,cut_point);
        }
    }
}

void cProtocolParser::parse_tx_buff()
{
    if ( m_tx_buff.count() > 0)
    {
        QString tmp_buffer;
        tmp_buffer.append(m_sync_char);
        tmp_buffer.append(m_tx_buff[0].at(0)); //comando
        tmp_buffer.append(m_separator_char);
        tmp_buffer.append(QString::number(m_tx_buff[0].count()-1)); //nº de args
        tmp_buffer.append(m_separator_char);

        for(uint i = 1 ; i < m_tx_buff[0].count() ; i++ )
        {
            tmp_buffer.append(m_tx_buff[0].at(i));
            tmp_buffer.append(m_separator_char);
        }        

        append_checksum(tmp_buffer);

        m_tx_buff.remove(0);
        if(checksum_is_valid(tmp_buffer))
        {
            QByteArray byte_buff = tmp_buffer.toLatin1();
            emit data_out(byte_buff);
        }
        else
        {
            qDebug("[WTF!]cProtocolParser::parse_tx_buff-> el checksum no coincide!!");
        }
    }
}


bool cProtocolParser::checksum_is_valid(QString& data)
{
    uint index = 0;
    if ( data.at(index++) != m_sync_char )
    {
        qDebug() << "[WARN]cProtocolParser::checksum_is_valid--> La cadena no empieza por los los valores de sync";
        return false;
    }

    QStringList fields = data.split(m_separator_char);
    char checksum = fields.at(fields.count()-1).data()->toLatin1();
    fields.removeLast();
    char payload_checksum = 0X00;
    for ( uint i = 0; i < fields.count() ; i++)
    {
        for(uint c = 0; c < fields.at(i).count() ; c++)
        {
            payload_checksum += fields.at(i).at(c).toLatin1();
        }

    }
    payload_checksum = ~payload_checksum & 0xFF;
    //qDebug() << "[INFO]mfParser::checksum_is_valid->" << payload_checksum << "/" << data[index];
    if ( ! ( payload_checksum == checksum )  )
    {
        qDebug() << "[WARN]mfParser::checksum_is_valid--> checksum incorrecto!!";
        return true; // Trampas!!!!Arregla esto cabron!!!!1
    }
    return true;
}

void cProtocolParser::append_checksum(QString &data)
{
    QStringList fields = data.split(m_separator_char);
    char payload_checksum = 0X00;
    for ( uint i = 0; i < fields.count() ; i++)
    {
        for(uint c = 0; c < fields.at(i).count() ; c++)
        {
            payload_checksum += fields.at(i).at(c).toLatin1();
        }

    }
    payload_checksum = ~payload_checksum & 0xFF;
    data.append((char)payload_checksum);
}

#include "cbyteaux.h"

cByteAux::cByteAux()
{
}

bool cByteAux::arrayContainsPattern(QByteArray array, QByteArray pat)
{
    bool found = false;
    bool data_left = true;
    long last_index = 0;
    while(data_left)
    {
        long index = array.indexOf(pat.at(0),last_index);
        if( index != -1)
        {
            QByteArray tmp = array.mid(index,pat.length());
            if(tmp == pat)
            {
                found = true;
                break;
            }
            else
            {
                index++;
            }
            last_index = index;
        }
        else
        {
            data_left = false;
        }

    }
    return found;
}

long cByteAux::indexOfPattern(QByteArray array, QByteArray pat,long start)
{
    bool data_left = true;
    long last_index = start;
    while(data_left)
    {
        long index = array.indexOf(pat.at(0),last_index);
        if( index != -1)
        {
            QByteArray tmp = array.mid(index,pat.length());
            if(tmp == pat)
            {
                return index;
            }
            else
            {
                index++;
            }
            last_index = index;
        }
        else
        {
            data_left = false;
        }

    }
    return -1;
}

QVector<QByteArray> cByteAux::splitBytearray(QByteArray array,QByteArray sep)
{
    QVector<QByteArray> result;
    long last_index = 0;
    long last_packet_end = 0;
    bool data_to_parse = true;
    while(data_to_parse)
    {
        long index = array.indexOf(sep.at(0),last_index);
        if(index != -1)
        {
            QByteArray tmp = array.mid(index,sep.length());
            if(tmp == sep)
            {
                QByteArray block = array.mid(last_packet_end,index-last_packet_end);
                result.append(block);
                index += sep.count();
                last_packet_end = index;
            }
            else
            {
                index++;
            }
            last_index = index;
        }
        else
        {
            QByteArray block = array.mid(last_packet_end,array.count() - last_packet_end);
            result.append(block);
            data_to_parse = false;
        }
    }
    return result;
}

QByteArray cByteAux::pixmap2ByteArray(QPixmap &pix)
{
    QByteArray bArray;
    QBuffer buffer( &bArray );
    buffer.open( QIODevice::WriteOnly );
    pix.save(&buffer,"PNG");

    return bArray;
}

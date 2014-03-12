#include "cusersinfolist.h"
#include "cbyteaux.h"
#include <QDebug>

cUsersInfoList::cUsersInfoList(QVector<cUser> users)
{
    fill_seps();
    for(int i = 0 ; i < users.count() ; i++)
    {
        m_users.append(users[i].get_userInfo());
    }
}

cUsersInfoList::cUsersInfoList(QVector<cUserInfo> users)
{
    fill_seps();
    for(int i = 0 ; i < users.count() ; i++)
    {
        m_users.append(users[i]);
    }
}

cUsersInfoList::cUsersInfoList(QByteArray& raw_data)
{
    qDebug() << raw_data;
    fill_seps();
    if(cByteAux::indexOfPattern(raw_data,m_parser_begin) != 0)
    {
        qDebug("[ERROR]cUsersInfoList(QByteArray& raw_data)-> Los datos no empiezan por la cadena de inicio");
        return;
    }
    long end_index = cByteAux::indexOfPattern(raw_data,m_parser_end);
    if( end_index == -1)
    {
        qDebug("[ERROR]cUsersInfoList(QByteArray& raw_data)-> Los datos no tienen cadena de fin");
        return;
    }
    QByteArray clean_data = raw_data.mid(m_parser_begin.count(),(raw_data.count()-m_parser_begin.count()-m_parser_end.count()));
    QVector<QByteArray> datablocks = cByteAux::splitBytearray(clean_data,m_parser_sep);
    quint16 elements = datablocks[0].toInt();
    if( elements*2 != datablocks.count()-1)
    {
        qDebug() << "[ERROR]cUsersInfoList(QByteArray& raw_data)-> Numero de campos inesperado" << elements*2 << "/" << datablocks.count()-1;
        return;
    }
    for(int i = 1 ; i < datablocks.count() ; i++)
    {
        QString name = datablocks[i++];
        QPixmap pix;
        pix.loadFromData(datablocks[i],"PNG");
        qDebug() << "[INFO]cUsersInfoList(QByteArray& raw_data)->" << name << datablocks[i].count() << pix.size();
        m_users.append(cUserInfo(name,pix));
    }
}

QByteArray cUsersInfoList::to_QByteArray()
{
    QByteArray result;
    result.append(m_parser_begin);
    result.append(QString::number(m_users.count()));
    for(int i = 0 ; i < m_users.count() ;i++)
    {
        result.append(m_parser_sep);
        result.append(m_users[i].get_name());
        result.append(m_parser_sep);
        QPixmap pix(m_users[i].get_avatar());
        result.append(cByteAux::pixmap2ByteArray(pix));
    }
    result.append(m_parser_end);
    return result;
}

void cUsersInfoList::fill_seps()
{
    m_parser_begin = "<+<B>+>";
    m_parser_sep   = "<+<S>+>";
    m_parser_end   = "<+<E>+>";
}

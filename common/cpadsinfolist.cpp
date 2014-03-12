#include "cpadsinfolist.h"

cPadsInfoList::cPadsInfoList(QVector<cPadInfo> pads)
{
    fill_seps();
    m_pads = pads;
}

cPadsInfoList::cPadsInfoList(QByteArray &raw_data)
{
    fill_seps();
    if(cByteAux::indexOfPattern(raw_data,m_parser_begin) != 0)
    {
        qDebug("[ERROR]cPadsInfoList(QByteArray& raw_data)-> Los datos no empiezan por la cadena de inicio");
        return;
    }
    long end_index = cByteAux::indexOfPattern(raw_data,m_parser_end);
    if( end_index == -1)
    {
        qDebug("[ERROR]cPadsInfoList(QByteArray& raw_data)-> Los datos no tienen cadena de fin");
        return;
    }
    QByteArray clean_data = raw_data.mid(m_parser_begin.count(),(raw_data.count()-m_parser_begin.count()-m_parser_end.count()));
    QVector<QByteArray> datablocks = cByteAux::splitBytearray(clean_data,m_parser_sep);
    quint16 elements = datablocks[0].toInt();
    if( elements*3 != datablocks.count()-1)
    {
        qDebug() << "[ERROR]cPadsInfoList(QByteArray& raw_data)-> Numero de campos inesperado" << elements*3 << "/" << datablocks.count()-1;
        return;
    }
    for(int i = 1 ; i < datablocks.count() ; i++)
    {
        QString   id = datablocks[i++];
        QString name = datablocks[i++];
        QPixmap pix;
        pix.loadFromData(datablocks[i],"PNG");
        //qDebug() << "[INFO]cPadsInfoList(QByteArray& raw_data)->" << name << datablocks[i].count() << pix.size();
        m_pads.append(cPadInfo(id,name,pix));
    }
}


QByteArray cPadsInfoList::to_QByteArray()
{
    QByteArray result;
    result.append(m_parser_begin);
    result.append(QString::number(m_pads.count()));
    for(int i = 0 ; i < m_pads.count() ;i++)
    {
        result.append(m_parser_sep);
        result.append(m_pads[i].getId());
        result.append(m_parser_sep);
        result.append(m_pads[i].getName());
        result.append(m_parser_sep);
        result.append(cByteAux::pixmap2ByteArray(m_pads[i].getIcon()));
    }
    result.append(m_parser_end);
    return result;
}

void cPadsInfoList::fill_seps()
{
    m_parser_begin = "<+<B>+>";
    m_parser_sep   = "<+<S>+>";
    m_parser_end   = "<+<E>+>";
}

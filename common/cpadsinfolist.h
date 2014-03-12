#ifndef CPADSINFOLIST_H
#define CPADSINFOLIST_H
#include <QObject>
#include <QDebug>
#include "cbyteaux.h"
#include "cpadinfo.h"

class cPadsInfoList
{
public:
    cPadsInfoList(QVector<cPadInfo> pads);
    cPadsInfoList(QByteArray& raw_data);
    QByteArray to_QByteArray();
    QVector<cPadInfo>& get_pads() {return m_pads;}
private:
    QVector<cPadInfo>  m_pads;
    QByteArray         m_parser_begin;
    QByteArray         m_parser_sep;
    QByteArray         m_parser_end;
    void fill_seps();
};

#endif // CPADSINFOLIST_H

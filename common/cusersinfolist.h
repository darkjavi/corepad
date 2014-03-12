#ifndef CUSERSINFOLIST_H
#define CUSERSINFOLIST_H

#include <QVector>
#include "cuser.h"

class cUsersInfoList
{
public:
    cUsersInfoList(QVector<cUser> users);
    cUsersInfoList(QVector<cUserInfo> users);
    cUsersInfoList(QByteArray& raw_data);
    QByteArray to_QByteArray();
    QVector<cUserInfo> get_users() {return m_users;}
private:
    QVector<cUserInfo> m_users;
    QByteArray         m_parser_begin;
    QByteArray         m_parser_sep;
    QByteArray         m_parser_end;
    void fill_seps();
};

#endif // CUSERSINFOLIST_H

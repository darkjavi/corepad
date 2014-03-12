#ifndef CUSER_H
#define CUSER_H

#include <QObject>
#include <QString>
#include <QPixmap>

class cUserInfo
{
public:
    cUserInfo(){}
    cUserInfo(QString name,QPixmap avatar) : m_avatar(avatar),m_name(name){}
    const QPixmap&    get_avatar()      {return m_avatar;}
    const QString&    get_name()        {return m_name;}
private:
    QPixmap     m_avatar;
    QString     m_name;
};

class cUser
{
public:
   cUser();
   cUser(QString name, QPixmap avatar);
   cUserInfo get_userInfo();
   const QString&   get_userName()  {return m_name;}
   const QPixmap&   get_avatar()    {return m_avatar;}
private:
    QPixmap     m_avatar;
    QString     m_name;
};

#endif // CUSER_H

#ifndef CCHATINFO_H
#define CCHATINFO_H

#include "QString"

class cChatInfo
{
public:
    cChatInfo(QString id = "none",QString name = "none",quint16 userCount = 0);
    const QString&  get_id()        {return m_id;}
    const QString&  get_name()      {return m_name;}
    quint16         get_usercount() {return m_userCount;}
protected:
    QString     m_id;
    QString     m_name;
    quint16     m_userCount;
};

#endif // CCHATINFO_H

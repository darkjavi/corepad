#ifndef CCHATMSG_H
#define CCHATMSG_H

#include <QDateTime>
#include <QString>

class cChatMsg
{
public:
    cChatMsg(QString sender = "NONE", QString msg = "NONE", QDateTime timestamp = QDateTime::currentDateTime());
    const QString&   get_sender()     {return m_sender;}
    const QString&   get_message()    {return m_message;}
    const QDateTime& get_timestamp()  {return m_timestamp;}
protected:
    QString     m_sender;
    QString     m_message;
    QDateTime   m_timestamp;
};

#endif // CCHATMSG_H

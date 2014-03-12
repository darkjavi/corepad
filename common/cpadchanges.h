#ifndef CPADCHANGES_H
#define CPADCHANGES_H
#include <QString>
#include <QDateEdit>

class cPadChanges
{
public:
    cPadChanges();
private:
    QString m_user;
    QString m_text_added;
    QDateTime m_timestamp;
    quint16   m_deleted_chars;
};

#endif // CPADCHANGES_H

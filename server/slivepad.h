#ifndef SLIVEPAD_H
#define SLIVEPAD_H

#include <QObject>
#include <QTextDocument>
#include "../common/cclient.h"
#include "../common/cpadsinfolist.h"
#include "QTextCursor"

class sLivePad : public QObject
{
    Q_OBJECT
public:
    explicit sLivePad(QString id,QString name = "Default-pad",QPixmap icon = QPixmap("://icons/cplusplus.png"), QObject *parent = 0);
    void     add_client(cClient* n_client);
    cPadInfo get_padInfo();
    QString  get_id()    {return m_id;}
    QString  get_name()  {return m_name;}
    QPixmap  get_icon()  {return m_icon;}

private:
    QTextDocument   m_doc;
    QTextCursor*    m_textCursor;
    QList<cClient*> m_clients;
    QString         m_id;
    QString         m_name;
    QPixmap         m_icon;
    void connect_client(cClient* n_client);
    cUsersInfoList  userslist();
signals:
    void send_pad_userslist(QString id, cUsersInfoList userlist);
    void send_pad_document(QString id, QString& padText);
    void send_pad_changes(QString id,QString sender ,int pos, int del, int add, QString txt);
private slots:
    void get_pad_userslist(QString id);
    void get_pad_document(QString id);
    void pad_changes(QString id,QString sender ,int pos, int del, int add, QString txt);
    void remove(QObject* obj);
public slots:
    
};

#endif // SLIVEPAD_H

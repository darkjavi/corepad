#ifndef SSESSIONMANAGER_H
#define SSESSIONMANAGER_H

#include <QObject>
#include <QVector>
#include "scontentsession.h"

class sSessionManager : public QObject
{
    Q_OBJECT
public:
    explicit sSessionManager(QObject *parent = 0);
    QVector<sContentSession*> get_sessions()    {return m_sessions;}
private:
    QVector<sContentSession*> m_sessions;
signals:
private slots:
    void join_session(QString id);
    //void session_status(QString id, bool status, QString reason);
public slots:
    void connect_client(cClient* client);
    void disconnect_client(cClient* client);
};

#endif // SSESSIONMANAGER_H

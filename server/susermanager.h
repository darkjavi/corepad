#ifndef SUSERMANAGER_H
#define SUSERMANAGER_H

#include <QObject>

#include "ssessionmanager.h"

class sUserManager : public QObject
{
    Q_OBJECT
public:
    explicit sUserManager(QObject *parent = 0);
    void set_sesionManager(sSessionManager* manager) {m_session_manager = manager;}
private:
    sSessionManager*  m_session_manager;
    QList<cClient*> m_clients;

    void connect_client(cClient* client);
signals:
    void client_list(QList<cClient*>&);
private slots:
    void get_user_info();
    void user_info(cUser user);
public slots:
    void add_client(cClient*);
    void remove_client(QObject* obj);
    void get_sessions();
};

#endif // SUSERMANAGER_H

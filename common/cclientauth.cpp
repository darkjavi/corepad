#include "cclientauth.h"

cClientAuth::cClientAuth(cChannelUser *user_channel, quint8 type, QObject *pParent)
    : QObject(pParent)
{
    m_channel = user_channel;
    m_type = type;
    m_timer.setInterval(4000);
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(auth_timeout()));
    if(m_type == cClient::typeServerClient)
    {
        qDebug() << "[INFO] Modulo de autenticacion, rol cliente en el servidor" ;
        m_timer.start();
    }
    else
    {
        qDebug() << "[INFO] Modulo de autenticacion, rol cliente";
    }
    connect_channel();
}

void cClientAuth::connect_channel()
{
    connect(m_channel,SIGNAL(greet()),this,SLOT(greet()));
    connect(m_channel,SIGNAL(login(QString,QString)),this,SLOT(login(QString,QString)));
    connect(m_channel,SIGNAL(login_status(bool,QString)),this,SLOT(rcv_login_status(bool,QString)));
}

bool cClientAuth::check_username(const QString &user, const QString &passwd)
{
    if ( (user == "") || (passwd != "largoygrueso") )
    {
        return false;
    }
    return true;
}

void cClientAuth::login_start(const QString &user, const QString &passwd)
{
    m_timer.start();
    m_user = user;
    m_passwd = passwd;
    m_channel->send_greet();
}

void cClientAuth::auth_timeout()
{
    m_timer.stop();
    emit login_status(false,"Timeout!");
}

void cClientAuth::rcv_login_status(bool status, QString reason)
{
    if(m_type == cClient::typeClient)
    {
        m_timer.stop();
        emit login_status(status,reason);
    }

}

void cClientAuth::greet()
{
    //Si es el server devuelve el saludo, si el el cliente inicia el login
    if(m_type == cClient::typeServerClient)
    {
        m_channel->send_greet();
    }
    else
    {
        m_channel->send_login(m_user,m_passwd);
    }
}

void cClientAuth::login(const QString &user, const QString &passwd)
{
    if(m_type == cClient::typeServerClient)
    {
        m_user = user;
        m_passwd = passwd;
        m_timer.stop();
        if(check_username(user,passwd))
        {
            m_channel->send_login_status(true);
            emit login_status(true);
        }
        else
        {
            m_channel->send_login_status(false,"BAD_USERNAME");
            emit login_status(false);
        }
    }
}

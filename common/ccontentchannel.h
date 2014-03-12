#ifndef CCONTENTCHANNEL_H
#define CCONTENTCHANNEL_H

#include <QObject>
#include <QDebug>
#include <QVector>

//#include "cclient.h"
class cClient;
//Esto es notable:
//Hay que tener cuidado con los 'include loops', esto se produce cuando
//tienes una clase A que contiene la clase B, y la clase B necesita saber de A
//cuando lo unico que necesitas es guardar el puntero de A en B basta con hacer un "class A;" en B
//Si necesitaras acceder a los metodos de A en B, las directivas #ifndef CCONTENTCHANNEL_H deberian
//evitar el conflito de los includes, pero por lo menos en este caso no ha sido asi



class cContentChannel : public QObject
{
    Q_OBJECT
public:
    enum channelType
    {
        CHANNEL_UNKNOWN,
        CHANNEL_SERVER,
        CHANNEL_USER,
        CHANNEL_SESSION
    };
    explicit cContentChannel(QObject *parent = 0);
    void     set_parent_client(cClient* client) {m_parent_client = client;}
    cClient* get_parent_client()                {return m_parent_client;}
protected:
    quint8   m_channel_type;
    cClient* m_parent_client;
signals:
    void dataTX(const QVector<QByteArray>& data);
public slots:
    virtual  void dataRX(const QVector<QByteArray>& data) = 0;
};

#endif // CCONTENTCHANNEL_H

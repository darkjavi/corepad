#ifndef CCHANNELPARSER_H
#define CCHANNELPARSER_H

#include <QObject>
#include <QVector>
#include <QMutex>

#include "cchannelserver.h"
#include "cchanneluser.h"
#include "cchannelsession.h"

class cChannelParser : public QObject
{
    Q_OBJECT
public:
    explicit cChannelParser(QObject *parent = 0);

    QVector<cContentChannel*>&  channels()          {return m_channels;}
    cChannelServer&             channel_server()    {return m_channel_server;}
    cChannelUser&               channel_user()      {return m_channel_user;}
    cChannelSession&            channel_session()   {return m_channel_session;}
    void set_parent_client(cClient* client);
protected:
    QByteArray                  m_rx_buffer;
    QMutex                      m_rx_buffer_lock;
    QVector<cContentChannel*>   m_channels;
    cChannelServer              m_channel_server;
    cChannelUser                m_channel_user;
    cChannelSession             m_channel_session;

    bool checksum               (const QByteArray& data);
    QByteArray append_checksum  (const QByteArray& data);
    void process_datapacket     (QByteArray data);
    //static const QByteArray m_parser_sync       = "((SYNC))"; // MIRAR CUANDO HAYA TIEMPO......
    //static const QByteArray m_parser_separator  = "[*BLCK*]";
    QByteArray m_parser_sync;
    QByteArray m_parser_separator;
    QByteArray m_parser_eof;

    void    parse_rx_buffer();
signals:
    void parser_tx(const QByteArray& data);
private slots:
    void prepare_tx(const QVector<QByteArray> &data);
public slots:
    void parser_rx(const QByteArray& data);
};

#endif // CCHANNELPARSER_H

#ifndef CPROTOCOLPARSER_H
#define CPROTOCOLPARSER_H

#include <QThread>
#include <QVector>
#include <QString>
#include <QStringList>
#include <QDebug>

#define PROTOCOL_SYNC_CHAR      0x01
#define PROTOCOL_SEPARATOR_CHAR 0x02

class cProtocolParser : public QThread
{
    Q_OBJECT

public:
    explicit cProtocolParser(QObject *parent = 0);
    void run();

signals:
    void user(QVector<QString>);  //...
    void pad(QVector<QString>);     //...
    void session    (QVector<QString>);
    void greetings  (QVector<QString>);
    void chat       (QVector<QString>);
    void data_out   (QByteArray);

public slots:
    void send_user(QVector<QString> args);  //...
    void send_pad(QVector<QString> args);    //...
    void send_session   (QVector<QString> args);
    void send_greetings (QVector<QString> args);
    void send_chat      (QVector<QString> args);
    void data_in        (QByteArray& data);

private:
    void parse_rx_buff();
    void parse_tx_buff();
    bool checksum_is_valid(QString& data);
    void append_checksum(QString &data);
    QByteArray                  m_rx_buff;
    QVector<QVector<QString> >  m_tx_buff;
    static const char m_sync_char = PROTOCOL_SYNC_CHAR;
    static const char m_separator_char = PROTOCOL_SEPARATOR_CHAR;
};

#endif // CPROTOCOLPARSER_H

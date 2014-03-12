#ifndef CDATA_H
#define CDATA_H

#include <QObject>

class cData : public QObject
{
    Q_OBJECT
public:
    explicit cData(QObject *parent = 0);
             cData(QByteArray& data,QObject* parent);
             virtual QByteArray to_bytearray() = 0;
protected:
             virtual void from_bytearray() = 0;
signals:
    
public slots:
    
};

#endif // CDATA_H

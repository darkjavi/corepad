#ifndef CBYTEAUX_H
#define CBYTEAUX_H
#include <QVector>
#include <QByteArray>
#include <QPixmap>
#include <QBuffer>

class cByteAux
{
public:
    cByteAux();
    static QVector<QByteArray> splitBytearray(QByteArray array, QByteArray sep);
    static bool  arrayContainsPattern(QByteArray array, QByteArray pat);
    static long  indexOfPattern(QByteArray array, QByteArray pat,long start = 0);
    static QByteArray  pixmap2ByteArray(QPixmap& pix);
};

#endif // CBYTEAUX_H

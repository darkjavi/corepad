#ifndef CFILE_H
#define CFILE_H
#include <QString>
#include <QFile>
#include <QDir>
#include "cfilechanges.h"

class cFile
{
public:
    cFile() : m_ok(false) {}
    cFile(const cFile& obj);
    cFile(const QByteArray& raw_data);
    cFile(QString new_filename, QString maintainer);
    cFile(QString& infoFile);
    QByteArray to_QByteArray();
    //static cFile apply_changes(cFile file, cFileChanges changes);

protected:
    QFile    m_origFile;
    QFile    m_infoFile;
    QString  m_maintainer;
    quint32  m_line_count;
    bool     m_ok;
};

#endif // CFILE_H

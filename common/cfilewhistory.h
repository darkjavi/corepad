#ifndef CFILEWHISTORY_H
#define CFILEWHISTORY_H
#include "cfile.h"
#include "cfilechanges.h"

class cFileWHistory : public cFile
{
public:
    cFileWHistory() : cFile() {}
    cFileWHistory(const cFileWHistory& obj);
    cFileWHistory(const QByteArray& raw_data);
    cFileWHistory(QString new_filename, QString maintainer = "Someone@unknown");
    cFileWHistory(QString& infoFile);
    QByteArray to_QByteArray();

protected:
    QFile   m_changesFile;
    //QVector<cFileChanges> m_changes;

};

#endif // CFILEWHISTORY_H

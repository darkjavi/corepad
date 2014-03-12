#ifndef CFILEINFO_H
#define CFILEINFO_H
#include <QString>

class cFileInfo
{
public:
    cFileInfo(QString filename = "invalid");
    const QString& get_fileName()   {return m_filename;}
private:
    QString m_filename;
    quint64 m_lines;
    quint64 m_size;
};

#endif // CFILEINFO_H

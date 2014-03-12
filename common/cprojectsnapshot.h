#ifndef CPROJECTSNAPSHOT_H
#define CPROJECTSNAPSHOT_H

#include <QString>
#include "cfile.h"

class cProjectSnapshot
{
public:
    cProjectSnapshot();
private:
    QString       m_upstream_id;
    QString       m_upstream_name;
    QString       m_upstream_version;
    QList<cFile>  m_upstream_files;
};

#endif // CPROJECTSNAPSHOT_H

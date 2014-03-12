#ifndef CPROJECT_H
#define CPROJECT_H
#include <QString>
#include "cprojectsnapshot.h"
#include "cfilewhistory.h"

//PASAR A STATIC CONST!
#define m_project_file    "project.dat"
#define m_sandbox_dir     "SANDBOX"
#define m_snapshots_dir   "SNAPSHOTS"
#define m_sessions_dir    "SESSIONS"
#define m_subprojects_dir "SUBPROJECTS"

class cProjectInfo
{

};

class cProject
{
public:
    cProject() : m_ok(false){}
    cProject(QString infoFile);
    cProject(QString path, QString id,QString name,QString maintainer);

    cProject(const QByteArray& raw_data);
    QByteArray  to_QByteArray();
    bool        is_ok() {return m_ok;}
protected:
    QString       m_upstream_id;
    QString       m_upstream_name;
    QString       m_upstream_version;
    QString                 m_infoFile;
    QString                 m_id;
    QString                 m_name;
    QString                 m_version;
    QString                 m_maintainer;
    QList<cFileWHistory>    m_files;
    QList<cProject>         m_subProjects;
    QList<cProject>         m_sessions;
    QList<cProjectSnapshot> m_snapshots;

    QDir    m_rootDir;

    bool    m_ok;

    bool generate_infoFile();
    bool load_infoFile();
};

#endif // CPROJECT_H

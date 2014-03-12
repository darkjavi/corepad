#include "cproject.h"
#include <QDebug>

cProject::cProject(QString infoFile)
{
    m_infoFile = infoFile;
    if(!load_infoFile()) return;
    if(!m_rootDir.exists()) return;
    m_ok = false;
}

cProject::cProject(QString path, QString id, QString name, QString maintainer)
{
    qDebug() << "[INFO]cProject::cProject->Creando nuevo cProject en el disco";
    m_ok = false;
    m_id = id;
    m_name = name;
    m_maintainer = maintainer;
    QDir project_root(path);
    if(!project_root.exists())
    {
        qDebug() << "[ERROR]cProject::cProject->NO existe la carpeta:" << project_root.absolutePath();
        return;
    }
    if(!project_root.mkdir(id))
    {
        qDebug() << "[ERROR]cProject::cProject->No he podido crear" << project_root.absolutePath() << "/" << id;
        return;
    }
    project_root.cd(id);
    m_rootDir = project_root;
    m_infoFile = m_rootDir.absoluteFilePath(m_project_file);
    if((!m_rootDir.mkdir(m_sandbox_dir))     ||
       (!m_rootDir.mkdir(m_sessions_dir))    ||
       (!m_rootDir.mkdir(m_subprojects_dir)) ||
       (!generate_infoFile()))
    {
        qDebug() << "[ERROR]cProject::cProject->No he podido crear el esqueleto:" << m_rootDir.absolutePath();
        //limpiar lo que se ha empezado a crear?
        return;
    }
    m_ok = true;
}




cProject::cProject(const QByteArray &raw_data)
{


}

QByteArray cProject::to_QByteArray()
{
    QByteArray raw_data;

    return raw_data;
}


bool cProject::generate_infoFile()
{
    QString str;
    str.append("PROJECT-ID:").append(m_id).append("\n");
    str.append("PROJECT-NAME:").append(m_name).append("\n");
    str.append("PROJECT-MAINTAINER:").append(m_maintainer).append("\n");
    QFile infoFile(m_infoFile);
    if(!infoFile.open(QIODevice::WriteOnly)) return false;
    QByteArray data;
    data.append(str);
    if(infoFile.write(data) != data.count()) return false;
    return true;
}

bool cProject::load_infoFile()
{
    QFile infoFile(m_infoFile);
    if(!infoFile.open(QIODevice::ReadOnly)) return false;
    QFileInfo finfo(infoFile);
    m_rootDir = finfo.absoluteDir();
    QString raw_data(infoFile.readAll());
    QStringList data_lines(raw_data.split("\n"));
    if(data_lines.count() < 3) return false;
    QStringList field_id(data_lines[0].split(":"));
    QStringList field_name(data_lines[1].split(":"));
    QStringList field_maintainer(data_lines[2].split(":"));
    if((field_id.count()  != 2) ||
       (field_name.count()!= 2) ||
       (field_maintainer.count() != 2) ) return false;
    if(field_id[0]!="PROJECT-ID") return false;
    m_id = field_id[1];
    m_name = field_name[1];
    m_maintainer = field_maintainer[1];
    return true;
}

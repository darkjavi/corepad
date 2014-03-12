#include "sproject.h"

sProject::sProject(cProject project, QDir new_project_root, QObject *parent) :
    QObject(parent)
{//creamos nuevo project en el disco
    m_project = project;
    if(!m_project.is_ok());
    {
        m_ready = false;
        return;
    }
    m_project_root = new_project_root;
    if(m_project_root.exists())
    {
        m_ready = false;
        return;
    }
    if(!m_project_root.mkdir(m_project_root.absolutePath()))
    {
        m_ready = false;
        return;
    }
    QString file(m_project_root.absolutePath());
    QFile project_file(file);
    if(!project_file.open(QIODevice::WriteOnly))
    {
        m_ready = false;
        return;
        //Limpiar los ficheros!
    }
    QByteArray bytes(m_project.to_QByteArray());
    if(project_file.write(bytes) != bytes.count())
    {
        m_ready = false;
        return;
        //Limpiar los ficheros!
    }

    //ESCRIBIR LOS FICHEROS DEL PROJECT EN EL DISCO!!!!
    m_ready = true;
}

sProject::sProject(QDir project_root, QObject *parent) :
    QObject(parent)
{//cargamos el project desde el disco
    if(!project_root.exists())
    {
        m_ready = false;
        return;
    }
    m_project_root = project_root;
    QFile project_file(m_project_root.filePath("project.dat"));
    if(!project_file.open(QIODevice::ReadOnly))
    {
        m_ready = false;
        return;
    }
    m_project = cProject(project_file.readAll());
    if(!m_project.is_ok())
    {
        m_ready =false;
        return;
    }
    m_ready = true;
}

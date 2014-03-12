#include "cfile.h"

cFile::cFile(const cFile &obj)
{
    m_origFile.setFileName(obj.m_origFile.fileName());
    m_infoFile.setFileName(obj.m_infoFile.fileName());
    m_maintainer    = obj.m_maintainer;
    m_line_count    = obj.m_line_count;
    m_ok            = obj.m_ok;
}



cFile::cFile(const QByteArray& raw_data)
{//Constructor desde datos raw
    m_ok =false;
}

cFile::cFile(QString new_filename,QString maintainer)
{//Nuevo fichero
    m_ok =false;
    m_origFile.setFileName(new_filename);
    m_infoFile.setFileName(new_filename.append(".info"));
    m_maintainer = maintainer;
    if(m_origFile.exists())
    {
        return;
    }
    QDir path(QFileInfo(m_origFile).absoluteDir());
    if(!path.exists())
    {
        if(!path.mkdir(path.path()))
        {
            return;
        }
    }
    if(!m_origFile.open(QIODevice::WriteOnly))
    {
        return;
    }
    m_origFile.close();
    if(!m_infoFile.open(QIODevice::WriteOnly))
    {
        return;
    }
    QString file_info;
    file_info.append("FILE:").append(m_origFile.fileName()).append("\n");
    file_info.append("MAINTAINER:").append(m_maintainer).append("\n");
    QByteArray data;
    data.append(file_info);
    m_infoFile.write(data);
    m_infoFile.close();
    m_ok = true;
}

cFile::cFile(QString &infoFile)
{//Cargar desde disco
    m_ok = false;
    m_infoFile.setFileName(infoFile);
    if(!m_infoFile.exists())
    {
        return;
    }
    if(!m_infoFile.open(QIODevice::ReadOnly))
    {
        return;
    }
    QString raw_data(m_infoFile.readAll());
    m_infoFile.close();
    QStringList data_lines(raw_data.split("\n"));
    if(data_lines.count() < 2)
    {
        return;
    }
    QStringList field_file(data_lines[0].split(":"));
    if((field_file.count() != 2) || (field_file[0] != "FILE"))
    {
        return;
    }
    m_origFile.setFileName(field_file[1]);
    if(!m_origFile.exists())
    {
        return;
    }
    QStringList field_maintainer(data_lines[1].split(":"));
    if((field_maintainer.count() != 2) || (field_maintainer[0] != "MAINTAINER"))
    {
        return;
    }
    m_maintainer = field_maintainer[1];
    m_ok =true;
}

QByteArray cFile::to_QByteArray()
{//exportar a raw
    QByteArray raw_data;

    return raw_data;
}

#include "cfilewhistory.h"

cFileWHistory::cFileWHistory(const cFileWHistory &obj) : cFile(obj)
{
    m_changesFile.setFileName(obj.m_changesFile.fileName());
}


cFileWHistory::cFileWHistory(const QByteArray& raw_data) : cFile(raw_data)
{//recibir 2 qbytearray, para file y changes por separado?
    if(m_ok)
    {//m_ok esta a true si el constructor del padre ha recompuesto el objeto correctamente
     //
    }
}

cFileWHistory::cFileWHistory(QString new_filename, QString maintainer) :cFile(new_filename,maintainer)
{
    if(m_ok)
    {
        m_changesFile.setFileName(new_filename.append(".changes"));
        if(!m_changesFile.open(QIODevice::WriteOnly))
        {
            m_ok = false;
            return;
        }
        m_changesFile.close();
        m_infoFile.open(QIODevice::Append);
        QString data;
        data.append("CHANGES:").append(m_changesFile.fileName()).append("\n");
    }
}

cFileWHistory::cFileWHistory(QString& infoFile) : cFile(infoFile)
{
    if(!m_ok)
    {
        return;
    }
    m_ok = false;
    m_infoFile.open(QIODevice::ReadOnly);
    QString raw_data(m_infoFile.readAll());
    QStringList data_lines(raw_data.split("/n"));
    if(data_lines.count() < 3) return;
    QStringList changesFile_field(data_lines[2].split(":"));
    if(changesFile_field.count() != 2) return;
    m_changesFile.setFileName(changesFile_field[1]);
    if(!m_changesFile.exists()) return;
    m_ok = true;
}

QByteArray cFileWHistory::to_QByteArray()
{
    QByteArray raw_data;

    return raw_data;
}

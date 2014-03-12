#ifndef SPROJECT_H
#define SPROJECT_H

#include <QObject>
#include "../common/cproject.h"
#include <QDir>
#include <QFile>

class sProject : public QObject
{
    Q_OBJECT
public:
    explicit sProject(QDir project_root,QObject *parent = 0);//Este crea el project DESDE el disco
             sProject(cProject project,QDir new_project_root,QObject *parent = 0); // Este crea el project en disco

             bool is_ready() {return m_ready;}
private:
    cProject  m_project;
    QDir      m_project_root;
    bool      m_ready;
signals:
    
public slots:
    
};

#endif // SPROJECT_H

#ifndef CPADINFO_H
#define CPADINFO_H

#include <QString>
#include <QPixmap>

class cPadInfo
{
private:
  QString m_id;
  QString m_name;
  QPixmap m_icon;
  QString m_nUsers;

public:
  cPadInfo() : m_id("NONE"), m_name("Default"), m_icon("://icons/cpluscplus.png"), m_nUsers("0") {}
  cPadInfo(QString& id, QString name = "Default", QPixmap icon = QPixmap("://icons/cpluscplus.png")) :
      m_id(id), m_name(name), m_icon(icon), m_nUsers("0") {}

  QString& getId() { return m_id; }
  QString& getName() { return m_name; }
  QPixmap& getIcon() { return m_icon; }
  QString& getUserCount() { return m_nUsers; }
};

#endif // CPADINFO_H

#ifndef CSESSIONINFO_H
#define CSESSIONINFO_H

#include <QString>

class cSessionInfo
{
private:
  QString m_id;
  QString m_name;

public:
  cSessionInfo() : m_id("none"), m_name("none") {}
  cSessionInfo(QString rId, QString rName) : m_id(rId), m_name(rName) {}

  void setID(QString& rId) { m_id = rId; }
  void setName(QString& rName) { m_name = rName; }

  QString& getID() { return m_id; }
  QString& getName() { return m_name; }
};

#endif // CSESSIONINFO_H

#include "cchatinfo.h"

cChatInfo::cChatInfo(QString id, QString name, quint16 userCount)
{
    m_id        = id;
    m_name      = name;
    m_userCount = userCount;
}

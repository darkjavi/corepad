#include "cchatmsg.h"

cChatMsg::cChatMsg(QString sender, QString msg, QDateTime timestamp)
{
    m_sender    = sender;
    m_message   = msg;
    m_timestamp = timestamp;
}

#include "ccontentchannel.h"

cContentChannel::cContentChannel(QObject *parent) :
    QObject(parent)
{
    m_channel_type = CHANNEL_UNKNOWN;
}

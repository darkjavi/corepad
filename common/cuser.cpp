#include "cuser.h"
cUser::cUser()
{

}

cUser::cUser(QString name, QPixmap avatar)
{
    m_name = name;
    m_avatar = avatar;
}

cUserInfo cUser::get_userInfo()
{
    cUserInfo info(m_name,m_avatar.scaled(64,64));
    return info;
}

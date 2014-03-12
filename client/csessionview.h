#ifndef CSESSIONVIEW_H
#define CSESSIONVIEW_H

#include <QDockWidget>

#include "../common/cclient.h"
#include "../common/cusersinfolist.h"

namespace Ui {
class cSessionView;
}

class cSessionView : public QDockWidget
{
  Q_OBJECT
    
public:
  explicit cSessionView(cClient* pClient, QWidget *parent = 0);
  ~cSessionView();
    
private slots:  
  void session_status(QString id, bool status, QString reason);
  void session_userlist(QString id, cUsersInfoList userList);
  void pad_list(QString id, cPadsInfoList rPads);
  void chatroom_list(QString id, QVector<cChatInfo>& rChats);
  void client_disconnected();

private:
  Ui::cSessionView *ui;

  cClient* m_pClient;
};

#endif // CSESSIONVIEW_H

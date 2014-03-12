#ifndef CCHATROOMSVIEW_H
#define CCHATROOMSVIEW_H

#include <QDockWidget>

#include "../common/cclient.h"
#include "../common/cchatinfo.h"
#include "cchatroomview.h"

namespace Ui {
class cChatroomsView;
}

class cChatroomsView : public QDockWidget
{
  Q_OBJECT
    
public:
  explicit cChatroomsView(cClient* pClient, QWidget *parent = 0);
  ~cChatroomsView();
    
private slots:
  void session_status(QString id ,bool status,QString reason);
  void chatroom_status(QString id, bool status, QString reason);
  void client_disconnected();

private:
  Ui::cChatroomsView *ui;

  cClient* m_pClient;

  QVector<cChatroomView*> m_chats;
};

#endif // CCHATROOMSVIEW_H

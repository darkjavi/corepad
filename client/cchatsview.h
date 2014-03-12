#ifndef CCHATSVIEW_H
#define CCHATSVIEW_H

#include <QGroupBox>

#include "../common/cclient.h"
#include "../common/cchatinfo.h"
#include "cchatview.h"

namespace Ui {
class cChatsView;
}

class cChatsView : public QGroupBox
{
  Q_OBJECT
    
public:
  explicit cChatsView(cClient* pClient, QWidget *parent = 0);
  ~cChatsView();
    
private slots:
  void session_status(QString id ,bool status,QString reason);

  void table_helper(int row, int column);
  void chatroom_status(QString id, bool status, QString reason);
  void chatroom_list(QString id,QVector<cChatInfo>& chats);
  void client_disconnected();

private:
  Ui::cChatsView *ui;

  cClient* m_pClient;

  QVector<cChatView*> m_chats;
};

#endif // CCHATSVIEW_H

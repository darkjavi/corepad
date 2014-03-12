#ifndef CCHATROOMVIEW_H
#define CCHATROOMVIEW_H

#include <QWidget>

#include "../common/cclient.h"
#include "../common/cusersinfolist.h"

namespace Ui {
class cChatroomView;
}

class cChatroomView : public QWidget
{
  Q_OBJECT
    
public:
  explicit cChatroomView(cClient *client, QString id = "1234", QString name = "NONE", QWidget *parent = 0);
  ~cChatroomView();
  QString get_chatId() { return m_chatId; }

signals:
  void send_chatroom_msg(QString id, QVector<cChatMsg> msgs);

private slots:
  void sendMessage();
  void eraseMessage();
  void client_disconnected();
  void session_status(QString id, bool status, QString reason);
  void chatroom_status(QString id, bool status, QString reason);
  void chatroom_msg(QString id, QVector<cChatMsg> msgs);
  void chatroom_userlist(QString id, cUsersInfoList users);

private:
  bool eventFilter(QObject *pObj, QEvent *pEvent);
  void add_msg(cChatMsg& msg);

  Ui::cChatroomView *ui;

  QString  m_chatId;
  QString  m_chatName;

  cClient* m_pClient;
};

#endif // CCHATROOMVIEW_H

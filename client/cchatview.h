#ifndef CCHATVIEW_H
#define CCHATVIEW_H

#include <QWidget>

#include "../common/cclient.h"

namespace Ui {
class cChatView;
}

class cChatView : public QWidget
{
  Q_OBJECT

public:
  explicit cChatView(cClient *client, QString id = "1234", QString name = "NONE", QWidget *parent = 0);
  ~cChatView();
    QString get_chatId()        {return m_chatId;}

signals:
  void send_chatroom_msg(QString id, QVector<cChatMsg> msgs);
private slots:
  void sendMessage();
  void eraseMessage();
  void client_disconnected();
  void session_status(QString id, bool status, QString reason);
  void chatroom_status(QString id, bool status, QString reason);
  void chatroom_msg(QString id, QVector<cChatMsg> msgs);
public slots:

private:
  bool eventFilter(QObject *pObj, QEvent *pEvent);
  void add_msg(cChatMsg& msg);
  Ui::cChatView *ui;
  QString       m_chatId;
  QString       m_chatName;
  cClient*      m_client;
};

#endif // CCHATVIEW_H

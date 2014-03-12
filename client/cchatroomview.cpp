#include <QtGui>
#include <QVector>

#include "cchatroomview.h"
#include "ui_cchatroomview.h"

cChatroomView::cChatroomView(cClient* client, QString chatId, QString chatName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cChatroomView)
{
  ui->setupUi(this);
  m_chatId = chatId;
  m_chatName = chatName;
  m_pClient = client;

  connect(ui->sendButton,SIGNAL(released()),
          this,SLOT(sendMessage()));
  connect(ui->eraseButton,SIGNAL(released()),
          this,SLOT(eraseMessage()));
  ui->messageLineEdit->installEventFilter(this);

  connect(m_pClient, SIGNAL(disconnected()), this, SLOT(client_disconnected()));

  connect(&m_pClient->channel_session(),SIGNAL(session_status(QString,bool,QString)),
          this,SLOT(session_status(QString,bool,QString)));
  connect(&m_pClient->channel_session(),SIGNAL(chatroom_status(QString,bool,QString)),
          this,SLOT(chatroom_status(QString,bool,QString)));
  connect(&m_pClient->channel_session(),SIGNAL(chatroom_msg(QString,QVector<cChatMsg>)),
          this,SLOT(chatroom_msg(QString,QVector<cChatMsg>)));
  connect(this,SIGNAL(send_chatroom_msg(QString,QVector<cChatMsg>)),
          &m_pClient->channel_session(),SLOT(send_chatroom_msg(QString,QVector<cChatMsg>)));
  connect(&m_pClient->channel_session(), SIGNAL(chatroom_userlist(QString,cUsersInfoList)),
          this, SLOT(chatroom_userlist(QString,cUsersInfoList)));

  m_pClient->channel_session().send_get_chatroom_userlist(m_chatId);
}

cChatroomView::~cChatroomView()
{
  delete ui;
}

// private slots
void cChatroomView::sendMessage()
{
  if (ui->messageLineEdit->text().compare(tr("")) != 0)
  {
    QVector<cChatMsg> msgs;
    cChatMsg msg(m_pClient->get_userName(), ui->messageLineEdit->text());
    msgs.append(msg);
    eraseMessage();
    emit send_chatroom_msg(m_chatId, msgs);
  }
}

void cChatroomView::eraseMessage()
{
  if (ui->messageLineEdit->text().compare(tr("")) != 0)
  {
    ui->messageLineEdit->setText(tr(""));
  }
}

void cChatroomView::session_status(QString id, bool status, QString reason)
{
  if(!m_chatId.startsWith(id))
  {
    return;
  }

  if (status)
  {
    m_pClient->channel_session().send_join_chatroom(m_chatId);
  }
  else
  {
    this->setEnabled(false);
    cChatMsg msg(id,reason);
    add_msg(msg);
  }
}

//public  slots
void cChatroomView::chatroom_status(QString id, bool status, QString reason)
{
  if (id != m_chatId)
  {
    return;
  }

  if (status)
  {
    this->setEnabled(true);
    ui->chatTextEdit->clear();
    m_pClient->channel_session().send_get_chatroom_userlist(m_chatId);
  }
  else
  {
    this->setEnabled(false);
    cChatMsg msg(id,reason);
    add_msg(msg);
  }
}

void cChatroomView::chatroom_msg(QString id, QVector<cChatMsg> msgs)
{
  if(id != m_chatId)
  {
    return;
  }

  for (int i = 0 ; i < msgs.count() ; i++)
  {
    add_msg(msgs[i]);
  }
}

void cChatroomView::chatroom_userlist(QString id, cUsersInfoList users)
{
  if (id != m_chatId)
  {
    return;
  }

  ui->usersInfoGroupBox->setUsersInfo(users.get_users());
}

void cChatroomView::client_disconnected()
{
  chatroom_status(m_chatId, false, "Client disconnected");
}

// private methods
bool cChatroomView::eventFilter(QObject *pObj, QEvent *pEvent)
{
  if (pEvent->type() == QEvent::KeyPress)
  {
    qDebug() << pEvent;
    QKeyEvent* keyEvent = (QKeyEvent *)pEvent;
    qDebug() << keyEvent->key();
#ifdef Q_OS_ANDROID
    if ((keyEvent->key() == Qt::Key_Return) || (keyEvent->key() == Qt::Key_Enter) || keyEvent->key() == 16777220)
#else
    if ((keyEvent->key() == Qt::Key_Return) || (keyEvent->key() == Qt::Key_Enter))
#endif
    {
      sendMessage();

      return true;
    }
  }

  return false;
}

void cChatroomView::add_msg(cChatMsg &msg)
{
  QString timestamp_str(QString::number(msg.get_timestamp().toTime_t()));
  QString sender_str(msg.get_sender());
  QString msg_str(msg.get_message());
  ui->chatTextEdit->append(timestamp_str.append("-").append(sender_str).append(":"));
  ui->chatTextEdit->append(msg_str);
}

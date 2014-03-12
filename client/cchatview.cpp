#include <QtGui>
#include <QVector>

#include "cchatview.h"
#include "ui_cchatview.h"

cChatView::cChatView(cClient* client, QString chatId, QString chatName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cChatView)
{
  ui->setupUi(this);
  m_chatId = chatId;
  m_chatName = chatName;
  m_client = client;
  connect(ui->sendButton,SIGNAL(released()),
          this,SLOT(sendMessage()));
  connect(ui->eraseButton,SIGNAL(released()),
          this,SLOT(eraseMessage()));
  ui->messageLineEdit->installEventFilter(this);

  connect(client,SIGNAL(disconnected()),this,SLOT(client_disconnected()));

  connect(&client->channel_session(),SIGNAL(session_status(QString,bool,QString)),
          this,SLOT(session_status(QString,bool,QString)));

  connect(&client->channel_session(),SIGNAL(chatroom_status(QString,bool,QString)),
          this,SLOT(chatroom_status(QString,bool,QString)));

  connect(&client->channel_session(),SIGNAL(chatroom_msg(QString,QVector<cChatMsg>)),
          this,SLOT(chatroom_msg(QString,QVector<cChatMsg>)));

  connect(this,SIGNAL(send_chatroom_msg(QString,QVector<cChatMsg>)),
          &client->channel_session(),SLOT(send_chatroom_msg(QString,QVector<cChatMsg>)));

}

cChatView::~cChatView()
{
  delete ui;
}

// private slots
void cChatView::sendMessage()
{
  if (ui->messageLineEdit->text().compare(tr("")) != 0)
  {
    QVector<cChatMsg> msgs;
    cChatMsg msg(m_client->get_userName(),ui->messageLineEdit->text());
    msgs.append(msg);
    eraseMessage();
    emit send_chatroom_msg(m_chatId,msgs);
  }
}

void cChatView::eraseMessage()
{
  if (ui->messageLineEdit->text().compare(tr("")) != 0)
  {
    ui->messageLineEdit->setText(tr(""));
  }
}

void cChatView::session_status(QString id, bool status, QString reason)
{
    if(!m_chatId.startsWith(id))
    {
        return;
    }
    if(status)
    {
        m_client->channel_session().send_join_chatroom(m_chatId);
    }
    else
    {
        this->setEnabled(false);
        cChatMsg msg(id,reason);
        add_msg(msg);
    }

}

//public  slots
void cChatView::chatroom_status(QString id, bool status, QString reason)
{
    if(id != m_chatId)
    {
        return;
    }
    if(status)
    {
        this->setEnabled(true);
        ui->chatTextEdit->clear();
    }
    else
    {
        this->setEnabled(false);
        cChatMsg msg(id,reason);
        add_msg(msg);
    }
}

void cChatView::chatroom_msg(QString id, QVector<cChatMsg> msgs)
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

// private methods
bool cChatView::eventFilter(QObject *pObj, QEvent *pEvent)
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

void cChatView::add_msg(cChatMsg &msg)
{
    QString timestamp_str(QString::number(msg.get_timestamp().toTime_t()));
    QString sender_str(msg.get_sender());
    QString msg_str(msg.get_message());
    ui->chatTextEdit->append(timestamp_str.append("-").append(sender_str).append(":"));
    ui->chatTextEdit->append(msg_str);
}

void cChatView::client_disconnected()
{
    chatroom_status(m_chatId,false,"Client disconnected");
}

#include <QtGui>

#include "cchatroomsview.h"
#include "ui_cchatroomsview.h"

cChatroomsView::cChatroomsView(cClient *pClient, QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::cChatroomsView)
{
  ui->setupUi(this);

  m_pClient = pClient;

  connect(m_pClient,SIGNAL(disconnected()), this, SLOT(client_disconnected()));
  connect(&m_pClient->channel_session(), SIGNAL(session_status(QString,bool,QString)),
          this, SLOT(session_status(QString,bool,QString)));
  connect(&m_pClient->channel_session(), SIGNAL(chatroom_status(QString, bool, QString)),
          this, SLOT(chatroom_status(QString,bool,QString)));
}

cChatroomsView::~cChatroomsView()
{
  delete ui;
}

// private slots
void cChatroomsView::session_status(QString id ,bool status,QString reason)
{
  if (status)
  {
    this->setEnabled(true);
  }
  else
  {
    QErrorMessage errorMsg;
    QString msg("Error: Couldn't connect to chat_rooms... ");
    msg.append(id).append(", ");
    msg.append(reason);
    errorMsg.showMessage(msg);
    errorMsg.exec();
    this->setEnabled(false);
  }
}

void cChatroomsView::chatroom_status(QString id, bool status, QString reason)
{
  if (status)
  {
      for(int i = 0 ; i < m_chats.count() ; i++)
      {//Si ya le hemos creado no hacemos nada
          if (m_chats[i]->get_chatId() ==id)
          {
            qDebug() << "[INFO]cChatroomsView::chatroom_status-> ya le he creado!:" << m_chats[i]->get_chatId()  << "/" << id;
            return;
          }
      }
      cChatroomView* chat = new cChatroomView(m_pClient,id,id,this);
      m_chats.append(chat);
      ui->chatRoomsTabWidget->addTab(chat,id);
  }
  else
  {
      QErrorMessage errorMessage;
      QString msg("No se ha podido conectar al chat:");
      msg.append(id);
      msg.append(" Reason:");
      msg.append(reason);
      errorMessage.showMessage(msg);
      errorMessage.exec();
  }
}

void cChatroomsView::client_disconnected()
{
  ui->chatRoomsTabWidget->clear();
  this->setEnabled(false);
}

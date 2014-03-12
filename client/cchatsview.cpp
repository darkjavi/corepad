#include "cchatsview.h"
#include "ui_cchatsview.h"

#include <QErrorMessage>

cChatsView::cChatsView(cClient *pClient, QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::cChatsView)
{
  ui->setupUi(this);

  m_pClient = pClient;  
  connect(m_pClient,SIGNAL(disconnected()),this,SLOT(client_disconnected()));
  connect(&m_pClient->channel_session(), SIGNAL(session_status(QString,bool,QString)),
          this, SLOT(session_status(QString,bool,QString)));
  connect(ui->chatRoomsTableWidget, SIGNAL(cellDoubleClicked(int,int)),
          this, SLOT(table_helper(int,int)));

  connect(&m_pClient->channel_session(), SIGNAL(chatroom_list(QString,QVector<cChatInfo>&)),
          this, SLOT(chatroom_list(QString,QVector<cChatInfo>&)));
    connect(&m_pClient->channel_session(), SIGNAL(chatroom_status(QString, bool, QString)),
          this, SLOT(chatroom_status(QString,bool,QString)));
}

cChatsView::~cChatsView()
{
  delete ui;    
}

// private slots
void cChatsView::session_status(QString id ,bool status,QString reason)
{
  if (status)
  {
    this->setEnabled(true);
    m_pClient->channel_session().send_get_chatroom_list(id);
  }
  else
  {
    this->setEnabled(false);
  }
}

void cChatsView::table_helper(int row, int column)
{
  QString id = ui->chatRoomsTableWidget->item(row,0)->text();
  m_pClient->channel_session().send_join_chatroom(id);
}

void cChatsView::chatroom_status(QString id, bool status, QString reason)
{
    qDebug() << "[INFO]cChatsView::chatroom_status-> id:" << id  << "status" << status;
  if (status)
  {
      for(int i = 0 ; i < m_chats.count() ; i++)
      {//Si ya le hemos creado no hacemos nada
          if (m_chats[i]->get_chatId() ==id)
          {
            qDebug() << "[INFO]cChatsView::chatroom_status-> ya le he creado!:" << m_chats[i]->get_chatId()  << "/" << id;
            return;
          }
      }
      cChatView* chat = new cChatView(m_pClient,id,id,this);
      m_chats.append(chat);
      ui->tabWidget->addTab(chat,id);
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

void cChatsView::chatroom_list(QString id, QVector<cChatInfo>& chats)
{
  ui->chatRoomsTableWidget->clear();
  ui->chatRoomsTableWidget->setEnabled(true);
  ui->chatRoomsTableWidget->setColumnCount(3);
  ui->chatRoomsTableWidget->setRowCount(chats.count());

  for (int i = 0; i < chats.count(); i++)
  {
    QTableWidgetItem* pItemID = new QTableWidgetItem(chats[i].get_id());
    QTableWidgetItem* pItemName = new QTableWidgetItem(chats[i].get_name());
    QTableWidgetItem* pItemUsers = new QTableWidgetItem(chats[i].get_usercount());

    ui->chatRoomsTableWidget->setItem(i, 0, pItemID);
    ui->chatRoomsTableWidget->setItem(i, 1, pItemName);
    ui->chatRoomsTableWidget->setItem(i, 2, pItemUsers);
  }
}

void cChatsView::client_disconnected()
{
    ui->chatRoomsTableWidget->clear();
    ui->chatRoomsTableWidget->setEnabled(false);
}

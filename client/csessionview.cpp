#include <QtGui>

#include "csessionview.h"
#include "ui_csessionview.h"

cSessionView::cSessionView(cClient *pClient, QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::cSessionView)
{
  ui->setupUi(this);

  m_pClient = pClient;

  connect(m_pClient, SIGNAL(disconnected()), this, SLOT(client_disconnected()));

  connect(&m_pClient->channel_session(), SIGNAL(session_status(QString, bool,QString)),
          this, SLOT(session_status(QString, bool,QString)));
  connect(&m_pClient->channel_session(), SIGNAL(session_userlist(QString, cUsersInfoList)),
          this, SLOT(session_userlist(QString, cUsersInfoList)));
  connect(&m_pClient->channel_session(), SIGNAL(pad_list(QString, cPadsInfoList)),
          this, SLOT(pad_list(QString, cPadsInfoList)));
  connect(&m_pClient->channel_session(), SIGNAL(chatroom_list(QString,QVector<cChatInfo>&)),
          this, SLOT(chatroom_list(QString, QVector<cChatInfo>&)));
  //connect(&m_pClient->channel_session(), SIGNAL(chatroom_list(QString, cChatsInfoList)),
  //        this, SLOT(chatroom_list(QString, cChatsInfoList)));
  //connect(ui->usersInfoView, SIGNAL(),
  //        &m_pClient->channel_session(), SLOT());

  connect(ui->padsInfoView, SIGNAL(send_join_pad(QString)),
          &m_pClient->channel_session(), SLOT(send_join_pad(QString)));
  connect(ui->chatroomsInfoView, SIGNAL(send_join_chatroom(QString)),
          &m_pClient->channel_session(), SLOT(send_join_chatroom(QString)));
}

cSessionView::~cSessionView()
{
  delete ui;
}

// private slots
void cSessionView::session_status(QString id, bool status, QString reason)
{
  if (status)
  {
    m_pClient->channel_session().send_get_session_userlist(id);
    m_pClient->channel_session().send_get_pad_list(id);
    m_pClient->channel_session().send_get_chatroom_list(id);
    this->setEnabled(true);
  }
  else
  {
    this->setEnabled(false);

    QErrorMessage errorMessage;
    QString msg("No se ha podido conectar a la sesion: ");

    msg.append(id);
    msg.append(" Reason: ");
    msg.append(reason);

    errorMessage.showMessage(msg);
    errorMessage.exec();
  }
}

void cSessionView::session_userlist(QString id, cUsersInfoList userList)
{
  qDebug() << "user_list received..." << userList.get_users().count();
  ui->usersInfoView->setUsersInfo(userList.get_users());
}

void cSessionView::pad_list(QString id, cPadsInfoList padList)
{  
  ui->padsInfoView->setPadsListInfo(padList.get_pads());
}

void cSessionView::chatroom_list(QString id, QVector<cChatInfo>& rChats)
//void cSessionView::chatroom_list(QString id, cChatsInfoList chatList)
{
  ui->chatroomsInfoView->setChatroomsInfo(rChats);
  //ui->chatroomsInfoView->setChatroomsInfo(chatList.get_chats());
}

void cSessionView::client_disconnected()
{
  this->setEnabled(false);
}

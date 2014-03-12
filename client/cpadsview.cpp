#include <QtGui>

#include "cpadsview.h"
#include "ui_cpadsview.h"

cPadsView::cPadsView(cClient *pClient, QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::cPadsView)
{
  ui->setupUi(this);

  m_pClient = pClient;

  connect(m_pClient,SIGNAL(disconnected()), this, SLOT(client_disconnected()));
  connect(&m_pClient->channel_session(), SIGNAL(session_status(QString,bool,QString)),
          this, SLOT(session_status(QString,bool,QString)));
  connect(&m_pClient->channel_session(), SIGNAL(pad_status(QString, bool, QString)),
          this, SLOT(pad_status(QString,bool,QString)));
}

cPadsView::~cPadsView()
{
  delete ui;
}

// private slots
void cPadsView::session_status(QString id ,bool status, QString reason)
{
  if (status)
  {
    this->setEnabled(true);
  }
  else
  {
    QErrorMessage errorMsg;
    QString msg("Error: Couldn't connect to pad... ");
    msg.append(id);
    msg.append(", reason: ");
    msg.append(reason);
    errorMsg.showMessage(msg);
    errorMsg.exec();

    this->setEnabled(false);
  }
}

void cPadsView::pad_status(QString id, bool status, QString reason)
{
  if (status)
  {
    for(int i = 0 ; i < m_pads.count() ; i++)
    {//Si ya le hemos creado no hacemos nada
      if (m_pads[i]->getPadId() == id)
      {
        //qDebug() << "[INFO]cChatroomsView::chatroom_status-> ya le he creado!:" << m_pads[i]->get_padId()  << "/" << id;
        return;
      }
    }
    cPadView* chat = new cPadView(m_pClient,id,this);
    m_pads.append(chat);
    ui->padsTabWidget->addTab(chat,id);
  }
  else
  {
    QErrorMessage errorMessage;
    QString msg("Couldn't connect to pad... ");
    msg.append(id);
    msg.append(", reason: ");
    msg.append(reason);
    errorMessage.showMessage(msg);
    errorMessage.exec();
  }
}

void cPadsView::client_disconnected()
{
  ui->padsTabWidget->clear();
  this->setEnabled(false);
}

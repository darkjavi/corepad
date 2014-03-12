#include "csessionsview.h"
#include "ui_csessionsview.h"
#include <QErrorMessage>

cSessionsView::cSessionsView(cClient *pClient, QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::cSessionsView)
{
  ui->setupUi(this);

  m_pClient = pClient;
  connect(m_pClient,SIGNAL(disconnected()),this,SLOT(client_disconnected()));
  connect(m_pClient, SIGNAL(login_status(bool)), this, SLOT(enabledSession(bool)));
  connect(&m_pClient->channel_user(), SIGNAL(sessions_list(QVector<cSessionInfo>&)),
          this, SLOT(sessions_list(QVector<cSessionInfo>&)));
  connect(ui->sessionsTableWidget, SIGNAL(cellDoubleClicked(int,int)),
          this, SLOT(table_helper(int,int)));
  connect(&m_pClient->channel_session(), SIGNAL(session_status(QString, bool, QString)),
          this, SLOT(session_status(QString,bool,QString)));
}

cSessionsView::~cSessionsView()
{
  delete ui;
}

// private slots
void cSessionsView::enabledSession(bool status)
{
  if (status)
  {
    this->setEnabled(true);
    m_pClient->channel_user().send_get_sessions();
  }
  else
  {
    this->setEnabled(false);
  }
}

void cSessionsView::table_helper(int row, int column)
{  
  QString id = ui->sessionsTableWidget->item(row,0)->text();

  m_pClient->channel_session().send_join_session(id);
}

void cSessionsView::session_status(QString id, bool status, QString reason)
{
  if (!status)
  {
      QErrorMessage errorMessage;
      QString msg("No se ha podido conectar a la sesion:");
      msg.append(id);
      msg.append(" Reason:");
      msg.append(reason);
      errorMessage.showMessage(msg);
      errorMessage.exec();
  }
}

void cSessionsView::sessions_list(QVector<cSessionInfo>& sessions)
{
  ui->sessionsTableWidget->setColumnCount(2);
  ui->sessionsTableWidget->setRowCount(sessions.count());

  for (int i = 0; i < sessions.count(); i++)
  {
    QTableWidgetItem* pItemID = new QTableWidgetItem(sessions[i].getID());
    QTableWidgetItem* pItemName  = new QTableWidgetItem(sessions[i].getName());

    ui->sessionsTableWidget->setItem(i, 0, pItemID);
    ui->sessionsTableWidget->setItem(i, 1, pItemName);
  }
}

void cSessionsView::client_disconnected()
{
    ui->sessionsTableWidget->clear();
    this->setEnabled(false);
}

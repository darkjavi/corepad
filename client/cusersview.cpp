#include "cusersview.h"
#include "ui_cusersview.h"

cUsersView::cUsersView(cClient *pClient, QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::cUsersView)
{
  ui->setupUi(this);

  m_pClient = pClient;
}

cUsersView::~cUsersView()
{
  delete ui;
}

// private slots
void cUsersView::enabledSession(bool status)
{
  if (status)
  {
    this->setEnabled(true);
  }
  else
  {
    this->setEnabled(false);
  }
}

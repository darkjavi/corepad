#include "cclientview.h"
#include "ui_cclientview.h"

cClientView::cClientView(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::cClientView)
{
  ui->setupUi(this);

  m_pClient = new cClient(cClient::typeClient);
  if (m_pClient->isOpen())
  {
    ui->connectionStatuslabel->setText(tr("Connected..."));
  }

  connect(m_pClient,SIGNAL(connected()),
          this,SLOT(connectionEnabled()));
  connect(m_pClient,SIGNAL(error(QAbstractSocket::SocketError)),
          this,SLOT(connectionFailed(QAbstractSocket::SocketError)));
  connect(ui->connectButton,SIGNAL(clicked()),this,SLOT(toggleConnect()));  

  connect(m_pClient, SIGNAL(login_status(bool,QString)), this, SLOT(client_auth(bool,QString)));
}

cClientView::~cClientView()
{
  delete ui;
  delete m_pClient;
}

cClient* cClientView::getClient()
{
  return m_pClient;
}

// private slots
void cClientView::connectionEnabled()
{
  ui->connectionStatuslabel->setText(tr("Connected..."));
  ui->connectButton->setText(tr("disconnect"));
  ui->connectButton->setEnabled(true);
}

void cClientView::connectionFailed(QAbstractSocket::SocketError error)
{
  ui->connectionStatuslabel->setText(tr("La conexion ha fallado"));
  ui->connectButton->setText(tr("connect"));
  ui->connectButton->setEnabled(true);
}

void cClientView::toggleConnect()
{
  if (m_pClient->isOpen())
  {
    m_pClient->closeSocket();
    ui->connectButton->setText(tr("connect"));
  }
  else
  {
    QString host = ui->hostLineEdit->text();
    int port = ui->portLineEdit->text().toInt();

    m_pClient->init(ui->userLineEdit->text(), ui->passwordLineEdit->text(), host, port);
    ui->connectButton->setText(tr("connecting..."));
    ui->connectButton->setEnabled(false);
  }
}

void cClientView::client_auth(bool status, QString reason)
{
  if (status)
  {
    ui->connectionStatuslabel->setText(tr("Login ok..."));
  }
  else
  {
    m_pClient->close();
    QErrorMessage errorMessage;
    QString msg("¡Login incorrecto!\n");
    msg.append("Info: ").append(reason);
    errorMessage.showMessage(msg);
    errorMessage.exec();
    ui->connectionStatuslabel->setText(reason);
    ui->connectButton->setText(tr("connect"));
    ui->connectButton->setEnabled(true);
  }
}

#include "cuserview.h"
#include "ui_cuserview.h"


cUserView::cUserView(cClient *pClient, QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::cUserView)
{
  ui->setupUi(this);

  m_pAvatarDialog = new QFileDialog();
  m_pPadColorDialog = new QColorDialog();

  m_pClient = pClient;

  QPixmap pixmap = QPixmap(QString(tr(":/images/user_image.png"))).scaled(64,64);
  ui->avatarPushButton->setIcon(QIcon(pixmap));

  //QBoxLayout* pPadColorLayout = new QBoxLayout(QBoxLayout::LeftToRight);
  //ui->padColorPushButton->layout()->addWidget(m_pPadColorDialog);
  //ui->padColorPushButton->layout()->addWidget(m_pPadColorDialog); ->setLayout(pPadColorLayout);

  //ui->padColorPushButton->layout()->addWidget(m_pPadColorDialog);

  ui->nicknameLineEdit->setText(QString("test"));

  QColor color = QColor(255,255,255);
  QPalette palette = ui->padColorFrame->palette();
  palette.setColor(backgroundRole(),color);
  ui->padColorFrame->setPalette(palette);
  ui->padColorFrame->setAutoFillBackground(true);

  connect(&m_pClient->channel_user(), SIGNAL(user_info(cUser)),
          this, SLOT(user_info(cUser)));

  connect(ui->avatarPushButton, SIGNAL(pressed()),
          this, SLOT(avatarClicked()));
  connect(m_pAvatarDialog, SIGNAL(fileSelected(QString)),
          this, SLOT(avatarChanged(QString)));
  connect(ui->padColorPushButton, SIGNAL(pressed()),
          this, SLOT(padColorClicked()));
  connect(m_pPadColorDialog, SIGNAL(colorSelected(QColor)),
          this, SLOT(padColorChanged(QColor)));
}

cUserView::~cUserView()
{
  delete ui;
  delete m_pAvatarDialog;
  delete m_pPadColorDialog;
}

void cUserView::setNickName(QString &rNickName)
{
  ui->nicknameLineEdit->setText(rNickName);
}

// private slots
void cUserView::enabledSession(bool status)
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

void cUserView::user_info(cUser user)
{  
  ui->avatarPushButton->setIcon(QIcon(user.get_avatar().scaled(64,64)));
  ui->nicknameLineEdit->setText(user.get_userName());
}

void cUserView::avatarClicked()
{
  m_pAvatarDialog->show();
}

void cUserView::avatarChanged(QString avatarFile)
{
  QPixmap pixmap = QPixmap(avatarFile).scaled(64,64);
  ui->avatarPushButton->setIcon(QIcon(pixmap));
}

void cUserView::padColorClicked()
{
  m_pPadColorDialog->show();
}

void cUserView::padColorChanged(QColor padColor)
{
  QPalette palette = ui->padColorFrame->palette();
  palette.setColor(backgroundRole(), padColor);
  ui->padColorFrame->setPalette(palette);
  ui->padColorFrame->setAutoFillBackground(true);
}

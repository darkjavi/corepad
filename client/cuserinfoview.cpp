#include <QtGui>

#include "cuserinfoview.h"
#include "ui_cuserinfoview.h"

cUserInfoView::cUserInfoView(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::cUserInfoView)
{
  ui->setupUi(this);
}

cUserInfoView::cUserInfoView(cUserInfo& rUserInfo, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::cUserInfoView)
{
  ui->setupUi(this);

  ui->avatarPushButton->setIcon(QIcon(rUserInfo.get_avatar()));
  qDebug() << "size: " << rUserInfo.get_avatar().size();
  ui->nicknameLabel->setText(rUserInfo.get_name());
}

cUserInfoView::~cUserInfoView()
{
  delete ui;
}

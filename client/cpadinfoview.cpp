#include "cpadinfoview.h"
#include "ui_cpadinfoview.h"

cPadInfoView::cPadInfoView(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::cPadInfoView)
{
  ui->setupUi(this);
}

cPadInfoView::cPadInfoView(cPadInfo &rPadInfo, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::cPadInfoView)
{
  ui->setupUi(this);

  ui->idLabel->setText(rPadInfo.getId());
  ui->iconPushButton->setIcon(rPadInfo.getIcon());
  ui->nameLabel->setText(rPadInfo.getName());
  ui->usersLabel->setText(rPadInfo.getUserCount());
}

cPadInfoView::~cPadInfoView()
{
  delete ui;
}

const QString& cPadInfoView::getId()
{
  return ui->idLabel->text();
}

const QPixmap& cPadInfoView::getIcon()
{
  return ui->iconPushButton->icon().pixmap(32,32);
}

const QString& cPadInfoView::getName()
{
  return ui->nameLabel->text();
}

const QString& cPadInfoView::getUserCount()
{
  return ui->usersLabel->text();
}

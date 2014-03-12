#include <QtGui>

#include "cchatroominfoview.h"
#include "ui_cchatroominfoview.h"

cChatroomInfoView::cChatroomInfoView(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::cChatroomInfoView)
{
  ui->setupUi(this);
}

cChatroomInfoView::cChatroomInfoView(cChatInfo &rChatInfo, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::cChatroomInfoView)
{
  ui->setupUi(this);

  ui->idLabel->setText(rChatInfo.get_id());
  ui->nameLabel->setText(rChatInfo.get_name());
  ui->usersLabel->setText(QString::number(rChatInfo.get_usercount()));
}

cChatroomInfoView::~cChatroomInfoView()
{
  delete ui;
}

const QString& cChatroomInfoView::getId()
{
  return ui->idLabel->text();
}

const QString& cChatroomInfoView::getName()
{
  return ui->nameLabel->text();
}

const QString& cChatroomInfoView::getUsers()
{
  return ui->usersLabel->text();
}

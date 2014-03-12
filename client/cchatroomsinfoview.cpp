#include <QtGui>

#include "cchatroomsinfoview.h"
#include "ui_cchatroomsinfoview.h"

cChatroomsInfoView::cChatroomsInfoView(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::cChatroomsInfoView)
{
  ui->setupUi(this);

  connect(ui->chatroomInfoListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
          this, SLOT(list_helper(QListWidgetItem*)));
}

cChatroomsInfoView::~cChatroomsInfoView()
{
  delete ui;
}

void cChatroomsInfoView::setChatroomsInfo(QVector<cChatInfo> &rChatroomsInfo)
{
  ui->chatroomInfoListWidget->clear();

  for (int i = 0; i < rChatroomsInfo.count(); i++)
  {
    cChatroomInfoView* pChatroomInfoView = new cChatroomInfoView(rChatroomsInfo[i]);
    QListWidgetItem* pChatroomInfoItem = new QListWidgetItem();
    pChatroomInfoItem->setSizeHint(QSize(150,30));
    ui->chatroomInfoListWidget->addItem(pChatroomInfoItem);
    ui->chatroomInfoListWidget->setItemWidget(pChatroomInfoItem, pChatroomInfoView);
  }
}

// private slots
void cChatroomsInfoView::list_helper(QListWidgetItem *pItem)
{
  emit send_join_chatroom(((cChatroomInfoView*)ui->chatroomInfoListWidget->itemWidget(pItem))->getId());
}

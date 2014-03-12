#include "cusersinfoview.h"
#include "ui_cusersinfoview.h"

cUsersInfoView::cUsersInfoView(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::cUsersInfoView)
{
  ui->setupUi(this);

  connect(ui->userInfoListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
          this, SLOT(list_helper(QListWidgetItem*)));
}

cUsersInfoView::~cUsersInfoView()
{
  delete ui;
}

void cUsersInfoView::setUsersInfo(QVector<cUserInfo> usersInfo)
{
  ui->userInfoListWidget->clear();

  for (int i = 0; i < usersInfo.count(); i++)
  {
    cUserInfoView* pUserInfoView = new cUserInfoView(usersInfo[i]);
    QListWidgetItem* pUserInfoItem = new QListWidgetItem();
    pUserInfoItem->setSizeHint(QSize(150,30));
    ui->userInfoListWidget->addItem(pUserInfoItem);
    ui->userInfoListWidget->setItemWidget(pUserInfoItem, pUserInfoView);
  }
}

// private slots
void cUsersInfoView::list_helper(QListWidgetItem *pItem)
{
  //...user info: goals, projects, ...
}

#include "cpadsinfoview.h"
#include "ui_cpadsinfoview.h"

cPadsInfoView::cPadsInfoView(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::cPadsInfoView)
{
  ui->setupUi(this);

  connect(ui->padInfoListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
          this, SLOT(list_helper(QListWidgetItem*)));
}

cPadsInfoView::~cPadsInfoView()
{
  delete ui;
}

void cPadsInfoView::setPadsListInfo(QVector<cPadInfo> &rPadsInfo)
{
  ui->padInfoListWidget->clear();

  for (int i = 0; i < rPadsInfo.count(); i++)
  {
    cPadInfoView* pPadInfoView = new cPadInfoView(rPadsInfo[i]);
    QListWidgetItem* pPadInfoItem = new QListWidgetItem();
    pPadInfoItem->setSizeHint(QSize(150,32));
    ui->padInfoListWidget->addItem(pPadInfoItem);
    ui->padInfoListWidget->setItemWidget(pPadInfoItem, pPadInfoView);
  }
}

// private slots
void cPadsInfoView::list_helper(QListWidgetItem *pItem)
{
  emit send_join_pad(((cPadInfoView*)ui->padInfoListWidget->itemWidget(pItem))->getId());
}

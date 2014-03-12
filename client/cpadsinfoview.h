#ifndef CPADSINFOVIEW_H
#define CPADSINFOVIEW_H

#include <QGroupBox>
#include <QListWidgetItem>

#include "cpadinfoview.h"

namespace Ui {
class cPadsInfoView;
}

class cPadsInfoView : public QGroupBox
{
  Q_OBJECT
    
public:
  explicit cPadsInfoView(QWidget *parent = 0);
  ~cPadsInfoView();

  void setPadsListInfo(QVector<cPadInfo>& rPadsInfo);
    
signals:
  void send_join_pad(QString id);

private slots:
  void list_helper(QListWidgetItem* pItem);

private:
  Ui::cPadsInfoView *ui;
};

#endif // CPADSINFOVIEW_H

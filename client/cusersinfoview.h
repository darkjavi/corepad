#ifndef CUSERSINFOVIEW_H
#define CUSERSINFOVIEW_H

#include <QGroupBox>
#include <QListWidgetItem>

#include "cuserinfoview.h"

namespace Ui {
class cUsersInfoView;
}

class cUsersInfoView : public QGroupBox
{
  Q_OBJECT
    
public:
  explicit cUsersInfoView(QWidget *parent = 0);
  ~cUsersInfoView();

  void setUsersInfo(QVector<cUserInfo> usersInfo);
    
private slots:
  void list_helper(QListWidgetItem* pItem);

private:
  Ui::cUsersInfoView *ui;
};

#endif // CUSERSINFOVIEW_H

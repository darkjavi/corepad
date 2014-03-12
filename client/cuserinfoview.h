#ifndef CUSERINFOVIEW_H
#define CUSERINFOVIEW_H

#include <QFrame>

#include "../common/cuser.h"

namespace Ui {
class cUserInfoView;
}

class cUserInfoView : public QFrame
{
  Q_OBJECT
    
public:
  explicit cUserInfoView(QWidget *parent = 0);
  explicit cUserInfoView(cUserInfo& rUserInfo, QWidget *parent = 0);
  ~cUserInfoView();
    
private:
  Ui::cUserInfoView *ui;
};

#endif // CUSERINFOVIEW_H

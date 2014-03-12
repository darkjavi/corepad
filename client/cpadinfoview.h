#ifndef CPADINFOVIEW_H
#define CPADINFOVIEW_H

#include <QFrame>

#include "../common/cpadinfo.h"

namespace Ui {
class cPadInfoView;
}

class cPadInfoView : public QFrame
{
  Q_OBJECT
    
public:
  explicit cPadInfoView(QWidget *parent = 0);
  explicit cPadInfoView(cPadInfo& rPadInfo, QWidget *parent = 0);
  ~cPadInfoView();
    
  const QString& getId();
  const QPixmap& getIcon();
  const QString& getName();
  const QString& getUserCount();

private:
  Ui::cPadInfoView *ui;
};

#endif // CPADINFOVIEW_H

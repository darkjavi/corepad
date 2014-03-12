#ifndef CUSERSVIEW_H
#define CUSERSVIEW_H

#include <QGroupBox>

#include "../common/cclient.h"

namespace Ui {
class cUsersView;
}

class cUsersView : public QGroupBox
{
  Q_OBJECT
    
public:
  explicit cUsersView(cClient *pClient, QWidget *parent = 0);
  ~cUsersView();

private slots:
  void enabledSession(bool status);

private:
  Ui::cUsersView *ui;

  cClient* m_pClient;
};

#endif // CUSERSVIEW_H

#ifndef CPADSVIEW_H
#define CPADSVIEW_H

#include <QDockWidget>

#include "../common/cclient.h"
#include "cpadview.h"

namespace Ui {
class cPadsView;
}

class cPadsView : public QDockWidget
{
  Q_OBJECT
    
public:
  explicit cPadsView(cClient* pClient, QWidget *parent = 0);
  ~cPadsView();
    
private slots:
  void session_status(QString id ,bool status, QString reason);
  void pad_status(QString id, bool status, QString reason);
  void client_disconnected();

private:
  Ui::cPadsView *ui;

  cClient* m_pClient;

  QVector<cPadView*> m_pads;
};

#endif // CPADSVIEW_H

#ifndef CSESSIONSVIEW_H
#define CSESSIONSVIEW_H

#include <QGroupBox>

#include "../common/cclient.h"
#include "../common/csessioninfo.h"

namespace Ui {
class cSessionsView;
}

class cSessionsView : public QGroupBox
{
  Q_OBJECT
    
public:
  explicit cSessionsView(cClient* pClient, QWidget *parent = 0);
  ~cSessionsView();

private slots:
  void enabledSession(bool status);

  void table_helper(int row, int column);
  void session_status(QString id, bool status, QString reason);
  void sessions_list(QVector<cSessionInfo> &sessions);
  void client_disconnected();
private:
  Ui::cSessionsView *ui;

  cClient* m_pClient;
};

#endif // CSESSIONSVIEW_H

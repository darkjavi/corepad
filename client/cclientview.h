#ifndef CCLIENTVIEW_H
#define CCLIENTVIEW_H

#include <QGroupBox>
#include <QErrorMessage>

#include "../common/cclient.h"

namespace Ui {
class cClientView;
}

class cClientView : public QGroupBox
{
  Q_OBJECT
    
public:
  explicit cClientView(QWidget *parent = 0);
  ~cClientView();

  cClient* getClient();
    
signals:
  void sessionReady();

private slots:
  void connectionEnabled();
  void connectionFailed(QAbstractSocket::SocketError error);
  void toggleConnect();
  void client_auth(bool status, QString reason);

private:
  Ui::cClientView *ui;

  cClient* m_pClient;
};

#endif // CCLIENTVIEW_H

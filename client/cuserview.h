#ifndef CUSERVIEW_H
#define CUSERVIEW_H

#include <QGroupBox>
#include <QFileDialog>
#include <QColorDialog>

#include "../common/cclient.h"

namespace Ui {
class cUserView;
}

class cUserView : public QGroupBox
{
  Q_OBJECT
    
public:
  explicit cUserView(cClient* pClient, QWidget *parent = 0);
  ~cUserView();

  void setNickName(QString& rNickName);
    
private slots:
  void enabledSession(bool status);
  void user_info(cUser user);

  void avatarClicked();
  void avatarChanged(QString avatarFile);
  void padColorClicked();
  void padColorChanged(QColor padColor);

private:
  Ui::cUserView *ui;

  QFileDialog* m_pAvatarDialog;
  QColorDialog* m_pPadColorDialog;

  cClient* m_pClient;

  //QColor* m_pColor;
};

#endif // CUSERVIEW_H

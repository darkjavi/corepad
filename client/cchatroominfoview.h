#ifndef CCHATROOMINFOVIEW_H
#define CCHATROOMINFOVIEW_H

#include <QFrame>
#include <QString>

#include "../common/cchatinfo.h"

namespace Ui {
class cChatroomInfoView;
}

class cChatroomInfoView : public QFrame
{
  Q_OBJECT
    
public:
  explicit cChatroomInfoView(QWidget *parent = 0);
  explicit cChatroomInfoView(cChatInfo& rChatInfo, QWidget *parent = 0);
  ~cChatroomInfoView();
    
  const QString& getId();
  const QString& getName();
  const QString& getUsers();

private:
  Ui::cChatroomInfoView *ui;
};

#endif // CCHATROOMINFOVIEW_H

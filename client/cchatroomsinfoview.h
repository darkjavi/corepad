#ifndef CCHATROOMSINFOVIEW_H
#define CCHATROOMSINFOVIEW_H

#include <QGroupBox>
#include <QListWidgetItem>

#include "cchatroominfoview.h"

namespace Ui {
class cChatroomsInfoView;
}

class cChatroomsInfoView : public QGroupBox
{
  Q_OBJECT
    
public:
  explicit cChatroomsInfoView(QWidget *parent = 0);
  ~cChatroomsInfoView();

  void setChatroomsInfo(QVector<cChatInfo>& rChatroomsInfo);
    
signals:
  void send_join_chatroom(QString id);

private slots:
  void list_helper(QListWidgetItem* pItem);

private:
  Ui::cChatroomsInfoView *ui;
};

#endif // CCHATROOMSINFOVIEW_H

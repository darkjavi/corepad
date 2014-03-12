#ifndef CMAINVIEW_H
#define CMAINVIEW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QSplitter>
#include <QMenuBar>

#include "cuserview.h"
#include "cpadsview.h"
#include "cchatroomsview.h"
#include "cusersinfoview.h"
#include "csessionview.h"
#include "csessionsview.h"
#include "cclientview.h"

class cMainView : public QMainWindow
{
  Q_OBJECT
public:
  explicit cMainView(QWidget *parent = 0);
  ~cMainView();
    
private slots:
  void showPadsView();
  void showSessionView();
  void showChatroomsView();

private:
  void createActions();
  void createMenuBar();
  void createMainView();

  QMenu* m_pViewsMenu;
  //QMenu* m_pHelpMenu;

  QAction* m_pPadsViewAction;
  QAction* m_pSessionViewAction;
  QAction* m_pChatroomsViewAction;
  //QAction* m_pAboutAction;

  QSplitter* m_pMainSplitter;
  QSplitter* m_pLeftSplitter;
  QSplitter* m_pRightSplitter;

  cUserView* m_pUser;
  cClientView* m_pClient;
  cPadsView* m_pPads;
  cChatroomsView* m_pChats;
  cSessionsView* m_pSessions;
  cSessionView* m_pSession;
};

#endif // CMAINVIEW_H

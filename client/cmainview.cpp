#include <QtGui>

#include "cmainview.h"

cMainView::cMainView(QWidget *parent) :
    QMainWindow(parent)
{
  createActions();
  createMenuBar();
  createMainView();
}

cMainView::~cMainView()
{  
  //delete m_pUser;
  //delete m_pPad;
  //delete m_pChats;
  //delete m_pSessions;
  //delete m_pSession;
  m_pClient->getClient()->close();
  //delete m_pClient;

  //delete m_pLeftSplitter;
  //delete m_pRightSplitter;
  //delete m_pMainSplitter;
}

// private slots
void cMainView::showPadsView()
{
  if (!m_pPads->isVisible())
  {
    m_pPads->setVisible(true);
  }
}

void cMainView::showSessionView()
{
  if (!m_pSession->isVisible())
  {
    m_pSession->setVisible(true);
  }
}

void cMainView::showChatroomsView()
{
  if (!m_pChats->isVisible())
  {
    m_pChats->setVisible(true);
  }
}

// private methods
void cMainView::createActions()
{
  m_pPadsViewAction = new QAction(tr("pads_view"), this);
  m_pPadsViewAction->setIcon(QIcon(":/images/pad.png"));
  m_pPadsViewAction->setStatusTip(tr("show pad view"));
  connect(m_pPadsViewAction, SIGNAL(triggered()), this, SLOT(showPadsView()));

  m_pSessionViewAction = new QAction(tr("session_view"), this);
  m_pSessionViewAction->setIcon(QIcon(":/images/session.png"));
  m_pSessionViewAction->setStatusTip(tr("show session view"));
  connect(m_pSessionViewAction, SIGNAL(triggered()), this, SLOT(showSessionView()));

  m_pChatroomsViewAction = new QAction(tr("chatrooms_view"), this);
  m_pChatroomsViewAction->setIcon(QIcon(":/images/chatrooms.png"));
  m_pChatroomsViewAction->setStatusTip(tr("show chatrooms view"));
  connect(m_pChatroomsViewAction, SIGNAL(triggered()), this, SLOT(showChatroomsView()));
}

void cMainView::createMenuBar()
{
  this->menuBar()->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

  m_pViewsMenu = menuBar()->addMenu(tr("&views"));
  m_pViewsMenu->addAction(m_pPadsViewAction);
  m_pViewsMenu->addAction(m_pSessionViewAction);
  m_pViewsMenu->addAction(m_pChatroomsViewAction);
}

void cMainView::createMainView()
{
  m_pClient = new cClientView();
  m_pUser = new cUserView(m_pClient->getClient());
  m_pUser->setEnabled(true);
  m_pPads = new cPadsView(m_pClient->getClient());
  m_pPads->setEnabled(false);
  m_pChats = new cChatroomsView(m_pClient->getClient());
  m_pChats->setEnabled(false);
  m_pSessions = new cSessionsView(m_pClient->getClient());
  m_pSessions->setEnabled(false);
  m_pSession = new cSessionView(m_pClient->getClient());
  m_pSession->setEnabled(false);

  m_pLeftSplitter = new QSplitter(Qt::Vertical);
  m_pLeftSplitter->addWidget(m_pClient);
  m_pLeftSplitter->addWidget(m_pPads);

  m_pRightSplitter = new QSplitter(Qt::Vertical);
  m_pRightSplitter->addWidget(m_pSession);
  m_pRightSplitter->addWidget(m_pSessions);
  m_pRightSplitter->addWidget(m_pChats);

  m_pMainSplitter = new QSplitter(Qt::Horizontal);
  m_pMainSplitter->addWidget(m_pUser);
  m_pMainSplitter->addWidget(m_pLeftSplitter);
  m_pMainSplitter->addWidget(m_pRightSplitter);

  this->setCentralWidget(m_pMainSplitter);
  this->showMaximized(); 
}

#include <QtGui>

#include "cpadview.h"
#include "ui_cpadview.h"

cPadView::cPadView(cClient *pClient, QString id, QWidget *pParent) :
    QWidget(pParent),
    ui(new Ui::cPadView)
{
  ui->setupUi(this);
  //ui->padTextEdit->setDocument(pDoc);
  m_remoteCursor = new QTextCursor(ui->padTextEdit->document());
  m_padId = id;
  m_pClient = pClient;
  m_padInit = false;

  this->setupPad();

  connect(m_pClient, SIGNAL(disconnected()), this, SLOT(client_disconnected()));

  connect(&m_pClient->channel_session(), SIGNAL(session_status(QString,bool,QString)),
          this, SLOT(session_status(QString,bool,QString)));
  connect(&m_pClient->channel_session(), SIGNAL(pad_status(QString,bool,QString)),
          this, SLOT(pad_status(QString,bool,QString)));

  connect(&m_pClient->channel_session(), SIGNAL(pad_document(QString, QString&)),
          this, SLOT(pad_document(QString, QString&)));
  connect(ui->padTextEdit->document(),SIGNAL(contentsChange(int,int,int)),this,SLOT(pad_tracker(int,int,int)));
  connect(&m_pClient->channel_session(),SIGNAL(pad_changes(QString,QString,int,int,int,QString)),this,SLOT(pad_changes(QString,QString,int,int,int,QString)));
  m_pClient->channel_session().send_get_pad_document(m_padId);
}

cPadView::~cPadView()
{
  delete ui;
  delete m_pHighlighter;
  //delete m_remoteCursor
}

void cPadView::setHighlighter(short mode)
{
  switch(mode)
  {
    case HIGHLIGHT_C:
      {
        if (m_pHighlighter)
        {
          delete m_pHighlighter;
        }
        m_pHighlighter = new cHighlighterCPlusPlus(ui->padTextEdit->document());
      }
      break;
    case HIGHLIGHT_C_PLUS_PLUS:
      {
        if (m_pHighlighter)
        {
          delete m_pHighlighter;
        }
        m_pHighlighter = new cHighlighterCPlusPlus(ui->padTextEdit->document());
      }
      break;
    case HIGHLIGHT_QT:
      {
        if (m_pHighlighter)
        {
          delete m_pHighlighter;
        }
        m_pHighlighter = new cHighlighterQT(ui->padTextEdit->document());
      }
      break;
  }
}

// private slots
void cPadView::pad_document(QString id, QString& rPadText)
{
  qDebug() << "pad_text: " << rPadText;

  if (m_padId != id)
  {
    return;
  }

  ui->padTextEdit->setPlainText(rPadText);
  m_padInit = true;
}

void cPadView::client_disconnected()
{
  pad_status(m_padId, false, "Client disconnected");
}

void cPadView::session_status(QString id, bool status, QString reason)
{
  if (!m_padId.startsWith(id))
  {
    return;
  }

  if (status)
  {
    m_pClient->channel_session().send_join_pad(m_padId);
  }
  else
  {
    this->setEnabled(false);
  }
}

void cPadView::pad_status(QString id, bool status, QString reason)
{
  if (id != m_padId)
  {
      return;
  }

  if (status)
  {
    this->setEnabled(true);
    ui->padTextEdit->clear();
    m_pClient->channel_session().send_get_pad_document(m_padId);
  }
  else
  {    
    this->setEnabled(false);
  }
}

void cPadView::pad_tracker( int pos, int rm , int add)
{
    if(!m_padInit)
    {
        return;
    }
    qDebug() << "PAD - " << ui->padTextEdit->textCursor().position() << (pos -rm+add) << pos << rm << add;
    if(ui->padTextEdit->textCursor().position() == (pos -rm+add))
    {
        QString text;
        if(add)
        {
            for( int i = pos ; i < pos+add ; i++ )
            {
                text.append(ui->padTextEdit->document()->characterAt(i));
            }
        }
        m_pClient->channel_session().send_pad_changes(m_padId,m_pClient->get_userName(),pos,rm,add,text);
    }
}

void cPadView::pad_changes(QString id, QString sender, int pos , int del, int add, QString txt)
{
    qDebug() << "PADD - " << m_pClient->get_userName() << m_remoteCursor->position() <<(pos -del+add) << pos << del << add;

    if( (m_padId != id) || (sender == m_pClient->get_userName()) )
    {
        return;
    }
    m_remoteCursor->setPosition(pos);
    for(int i = 0 ; i < del ; i++)
    {
        m_remoteCursor->deleteChar();
    }
    if(add)
    {
        m_remoteCursor->insertText(txt);
    }
}

// private methods
void cPadView::setupPad()
{
  QFont font;
  font.setFamily("Times New Roman");
  font.setFixedPitch(true);
  font.setPointSize(10);

  ui->padTextEdit->setFont(font);

  m_pHighlighter = new cHighlighterQT(ui->padTextEdit->document());  
}


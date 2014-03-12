#ifndef CPADVIEW_H
#define CPADVIEW_H

#include <QWidget>
#include <QTextCursor>

#include "../common/cclient.h"
#include "chighlighter.h"
#include "chighlightercplusplus.h"
#include "chighlighterqt.h"

#define HIGHLIGHT_C                 0
#define HIGHLIGHT_C_PLUS_PLUS       1
#define HIGHLIGHT_QT                2

namespace Ui {
class cPadView;
}

class cPadView : public QWidget
{
  Q_OBJECT
    
public:
  explicit cPadView(cClient* pClient, QString id = "1234", QWidget *pParent = 0);
  ~cPadView();

  const QString& getPadId() { return m_padId; }

  void setHighlighter(short mode);

private slots:
  void pad_document(QString id, QString& rPadText);
  void client_disconnected();
  void session_status(QString id, bool status, QString reason);
  void pad_status(QString id, bool status, QString reason);
  void pad_tracker(int, int, int add);
  void pad_changes(QString id, QString sender, int pos, int del, int add, QString txt);

private:
  void setupPad();

  Ui::cPadView *ui;

  cClient* m_pClient;

  QString m_padId;

  cHighlighter* m_pHighlighter;

  QTextCursor* m_remoteCursor;
  bool         m_padInit;
};

#endif // CPADVIEW_H

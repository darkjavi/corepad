#ifndef CHIGHLIGHTERQT_H
#define CHIGHLIGHTERQT_H

#include "chighlightercplusplus.h"

class cHighlighterQT : public cHighlighterCPlusPlus
{
  //Q_OBJECT
private:
  QRegExp m_commentStartExpression;
  QRegExp m_commentEndExpression;

  QTextCharFormat m_preprocessorFormat;
  QTextCharFormat m_directiveFormat;
  QTextCharFormat m_keywordFormat;
  QTextCharFormat m_classFormat;
  QTextCharFormat m_singleLineCommentFormat;
  QTextCharFormat m_multiLineCommentFormat;
  QTextCharFormat m_quotationFormat;
  QTextCharFormat m_functionFormat;

protected:
  void highlightBlock(const QString &text);

public:
  explicit cHighlighterQT(QTextDocument *pParent = 0);
};

#endif // CHIGHLIGHTERQT_H

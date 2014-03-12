#ifndef CHIGHLIGHTERCPLUSPLUS_H
#define CHIGHLIGHTERCPLUSPLUS_H

#include "chighlighter.h"

class cHighlighterCPlusPlus : public cHighlighter
{
  //Q_OBJECT

private:
  QRegExp m_commentStartExpression;
  QRegExp m_commentEndExpression;

  QTextCharFormat m_preprocessorFormat;
  QTextCharFormat m_keywordFormat;
  QTextCharFormat m_classFormat;
  QTextCharFormat m_singleLineCommentFormat;
  QTextCharFormat m_multiLineCommentFormat;
  QTextCharFormat m_quotationFormat;
  QTextCharFormat m_functionFormat;

protected:
  void highlightBlock(const QString &text);

public:
  explicit cHighlighterCPlusPlus(QTextDocument *pParent = 0);
};

#endif // CHIGHLIGHTERCPLUSPLUS_H

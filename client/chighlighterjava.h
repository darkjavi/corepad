#ifndef CHIGHLIGHTERJAVA_H
#define CHIGHLIGHTERJAVA_H

#include "chighlighter.h"

class cHighlighterJava : public cHighlighter
{
private:
  QRegExp m_commentStartExpression;
  QRegExp m_commentEndExpression;

  QTextCharFormat m_keywordFormat;
  QTextCharFormat m_classFormat;
  QTextCharFormat m_singleLineCommentFormat;
  QTextCharFormat m_multiLineCommentFormat;
  QTextCharFormat m_quotationFormat;
  QTextCharFormat m_functionFormat;

protected:
  void highlightBlock(const QString &text);

public:
  explicit cHighlighterJava(QTextDocument *pParent = 0);
};

#endif // CHIGHLIGHTERJAVA_H

#ifndef CHIGHLIGHTERPHP_H
#define CHIGHLIGHTERPHP_H

#include "chighlighter.h"

class cHighlighterPHP : public cHighlighter
{
private:
  QRegExp m_commentStartExpression;
  QRegExp m_commentEndExpression;

  QTextCharFormat m_predefinedConstantFormat;
  QTextCharFormat m_keywordFormat;
  QTextCharFormat m_classFormat;
  QTextCharFormat m_singleLineCommentFormat;
  QTextCharFormat m_multiLineCommentFormat;
  QTextCharFormat m_quotationFormat;
  QTextCharFormat m_functionFormat;

protected:
  void highlightBlock(const QString &text);

public:
  explicit cHighlighterPHP(QTextDocument *pParent = 0);
};

#endif // CHIGHLIGHTERPHP_H

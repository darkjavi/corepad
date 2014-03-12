#include "chighlighter.h"

cHighlighter::cHighlighter(QTextDocument *pParent) :
    QSyntaxHighlighter(pParent)
{
  //m_highlightingRules = QVector<stHighlightingRule>;
}

// protected methods
/*void cHighlighter::highlightBlock(const QString &text)
{
  foreach (const stHighlightingRule &rule, m_highlightingRules)
  {
    QRegExp expression(rule.m_pattern);
    int index = expression.indexIn(text);
    while (index >= 0)
    {
      int length = expression.matchedLength();
      setFormat(index, length, rule.m_format);
      index = expression.indexIn(text, index + length);
    }
  }

  setCurrentBlockState(0);

  int startIndex = 0;
  if (previousBlockState() != 1)
  {
    startIndex = m_commentStartExpression.indexIn(text);
  }

  while (startIndex >= 0)
  {
    int endIndex = m_commentEndExpression.indexIn(text, startIndex);
    int commentLength;
    if (endIndex == -1)
    {
      setCurrentBlockState(1);
      commentLength = text.length() - startIndex;
    } else
    {
      commentLength = endIndex - startIndex + m_commentEndExpression.matchedLength();
    }
    setFormat(startIndex, commentLength, multiLineCommentFormat);
    startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
  }
}*/

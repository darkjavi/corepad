#include "chighlighterjava.h"

// protected methods
void cHighlighterJava::highlightBlock(const QString &text)
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
    setFormat(startIndex, commentLength, m_multiLineCommentFormat);
    startIndex = m_commentStartExpression.indexIn(text, startIndex + commentLength);
  }
}

// public methods
cHighlighterJava::cHighlighterJava(QTextDocument *pParent) :
    cHighlighter(pParent)
{
  stHighlightingRule rule;

  // keywords...
  m_keywordFormat.setForeground(Qt::darkBlue);
  m_keywordFormat.setFontWeight(QFont::Bold);
  QStringList keywordPatterns;
  keywordPatterns << "\\babstract\\b" << "\\bcontinue\\b" << "\\bfor\\b" << "\\bnew\\b" << "\\bswitch\\b"
                  << "\\bassert	default\\b" << "\\bgoto\\b" << "\\bpackage\\b" << "\\bsynchronized\\b"
                  << "\\bboolean\\b" << "\\bdo\\b" << "\\bif\\b" << "\\bprivate\\b" << "\\bthis\\b"
                  << "\\bbreak\\b" << "\\bdouble\\b" << "\\bimplements\\b" << "\\bprotected\\b" << "\\bthrow\\b"
                  << "\\bbyte\\b" << "\\belse\\b" << "\\bimport\\b" << "\\bpublic\\b" << "\\bthrows\\b"
                  << "\\bcase\\b" << "\\benum\\b" << "\\binstanceof\\b" << "\\breturn\\b" << "\\btransient\\b"
                  << "\\bcatch\\b" << "\\bextends\\b" << "\\bint\\b" << "\\bshort\\b" << "\\btry\\b"
                  << "\\bchar\\b" << "\\bfinal\\b" << "\\binterface\\b" << "\\bstatic\\b" << "\\bvoid\\b"
                  << "\\bclass\\b" << "\\bfinally\\b" << "\\blong\\b" << "\\bstrictfp\\b" << "\\bvolatile\\b"
                  << "\\bconst\\b" << "\\bfloat\\b" << "\\bnative\\b" << "\\bsuper\\b" << "\\bwhile\\b";

  foreach (const QString &pattern, keywordPatterns)
  {
    rule.m_pattern = QRegExp(pattern);
    rule.m_format = m_keywordFormat;
    m_highlightingRules.append(rule);
  }

  m_classFormat.setFontWeight(QFont::Bold);
  m_classFormat.setForeground(Qt::darkMagenta);
  rule.m_pattern = QRegExp("\\bQ[A-Za-z]+\\b");
  rule.m_format = m_classFormat;
  m_highlightingRules.append(rule);

  m_singleLineCommentFormat.setForeground(Qt::red);
  rule.m_pattern = QRegExp("//[^\n]*");
  rule.m_format = m_singleLineCommentFormat;
  m_highlightingRules.append(rule);

  m_multiLineCommentFormat.setForeground(Qt::red);

  m_quotationFormat.setForeground(Qt::darkGreen);
  rule.m_pattern = QRegExp("\".*\"");
  rule.m_format = m_quotationFormat;
  m_highlightingRules.append(rule);

  m_functionFormat.setFontItalic(true);
  m_functionFormat.setForeground(Qt::blue);
  rule.m_pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
  rule.m_format = m_functionFormat;
  m_highlightingRules.append(rule);

  m_commentStartExpression = QRegExp("/\\*");
  m_commentEndExpression = QRegExp("\\*/");
}

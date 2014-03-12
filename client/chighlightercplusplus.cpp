#include <QtGui>

#include "chighlightercplusplus.h"

// protected methods
void cHighlighterCPlusPlus::highlightBlock(const QString &text)
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
cHighlighterCPlusPlus::cHighlighterCPlusPlus(QTextDocument *pParent) :
    cHighlighter(pParent)
{
  stHighlightingRule rule;

  // preprocessor directives...
  m_preprocessorFormat.setForeground(Qt::darkGreen);
  QStringList preprocessorPatterns;
  preprocessorPatterns << "#define" << "#elif" << "#endif"
                       << "#if" << "#ifdef" << "#ifndef"
                       << "#include" << "#undefine";
  foreach (const QString &pattern, preprocessorPatterns)
  {
    rule.m_pattern = QRegExp(pattern);
    rule.m_format = m_preprocessorFormat;
    m_highlightingRules.append(rule);
  }

  // keywords...
  m_keywordFormat.setForeground(Qt::darkBlue);
  m_keywordFormat.setFontWeight(QFont::Bold);
  QStringList keywordPatterns;
  keywordPatterns << "\\bbreak\\b" << "\\bcase\\b" << "\\bcatch\\b"
                  << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                  << "\\bcontinue\\b" << "\\bdefault\\b" << "\\bdelete\\b" << "\\bdo\\b"
                  << "\\bdouble\\b" << "\\belse\\b"
                  << "\\benum\\b" << "\\bexplicit\\b"
                  << "\\bfloat\\b" << "\\bfor\\b"
                  << "\\bfriend\\b" << "\\bgoto\\b" << "\\bif\\b"
                  << "\\binline\\b" << "\\bint\\b"
                  << "\\blong\\b" << "\\bnamespace\\b" << "\\bnew\\b" << "\\boperator\\b"
                  << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                  << "\\breturn\\b"
                  << "\\bshort\\b" << "\\bsigned\\b" << "\\bsizeof\\b"
                  << "\\bstatic\\b" << "\\bstruct\\b"
                  << "\\bswitch\\b"
                  << "\\btemplate\\b" << "\\bthis\\b" << "\\btypedef\\b" << "\\bthrow\\b"
                  << "\\btry\\b" << "\\btypename\\b"
                  << "\\bunion\\b" << "\\busing\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                  << "\\bvoid\\b" << "\\bvolatile\\b"
                  << "\\bwhile\\b";
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

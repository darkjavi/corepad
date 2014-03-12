#include "chighlighterphp.h"

// protected methods
void cHighlighterPHP::highlightBlock(const QString &text)
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
cHighlighterPHP::cHighlighterPHP(QTextDocument *pParent) :
    cHighlighter(pParent)
{
    stHighlightingRule rule;

    // predefined constants...
    m_predefinedConstantFormat.setForeground(Qt::darkBlue);
    QStringList predefinedConstantPatterns;
    predefinedConstantPatterns << "\\b__CLASS__\\b" << "\\b__DIR__\\b" << "\\b__FILE__\\b"
                               << "\\b__FUNCTION__\\b" << "\\b__LINE__\\b" << "\\b__METHOD__\\b"
                               << "\\b__NAMESPACE__\\b" << "\\b__TRAIT__\\b";
    foreach (const QString &pattern, predefinedConstantPatterns)
    {
      rule.m_pattern = QRegExp(pattern);
      rule.m_format = m_predefinedConstantFormat;
      m_highlightingRules.append(rule);
    }

    // keywords...
    m_keywordFormat.setForeground(Qt::darkBlue);
    m_keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\b__halt_compiler()\\b" << "\\babstract\\b" << "\\band\\b" << "\\barray()\\b" << "\\bas\\b"
                    << "\\bbreak\\b" << "\\bcallable\\b" << "\\bcase\\b" << "\\bcatch\\b" << "\\bclass\\b"
                    << "\\bclone\\b" << "\\bconst\\b" << "\\bcontinue\\b" << "\\bdeclare\\b" << "\\bdefault\\b"
                    << "\\bdie()\\b" << "\\bdo\\b" << "\\becho\\b" << "\\belse\\b" << "\\belseif\\b"
                    << "\\bempty()\\b" << "\\benddeclare\\b" << "\\bendfor\\b" << "\\bendforeach\\b" << "\\bendif\\b"
                    << "\\bendswitch\\b" << "\\bendwhile\\b" << "\\beval()\\b" << "\\bexit()\\b" << "\\bextends\\b"
                    << "\\bfinal\\b" << "\\bfor\\b" << "\\bforeach\\b" << "\\bfunction\\b" << "\\bglobal\\b"
                    << "\\bgoto\\b" << "\\bif\\b" << "\\bimplements\\b" << "\\binclude\\b" << "\\binclude_once\\b"
                    << "\\binstanceof\\b" << "\\binsteadof\\b" << "\\binterface\\b" << "\\bisset()\\b" << "\\blist()\\b"
                    << "\\bnamespace\\b" << "\\bnew\\b" << "\\bor\\b" << "\\bprint\\b" << "\\bprivate\\b"
                    << "\\bprotected\\b" << "\\bpublic\\b" << "\\brequire\\b" << "\\brequire_once\\b" << "\\breturn\\b"
                    << "\\bstatic\\b" << "\\bswitch\\b" << "\\bhrow\\b" << "\\btrait\\b" << "\\btry\\b"
                    << "\\bunset()\\b" << "\\buse\\b" << "\\bvar\\b" << "\\bwhile\\b" << "\\bxor\\b";
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

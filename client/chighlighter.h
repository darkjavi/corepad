#ifndef CHIGHLIGHTER_H
#define CHIGHLIGHTER_H

#include <QSyntaxHighlighter>

struct stHighlightingRule
{
  QRegExp m_pattern;
  QTextCharFormat m_format;
};

class cHighlighter : public QSyntaxHighlighter
{
  Q_OBJECT

protected:
  QVector<stHighlightingRule> m_highlightingRules;

public:
  explicit cHighlighter(QTextDocument *pParent = 0);
    
//protected:
//  void highlightBlock(const QString &text);
};

#endif // CHIGHLIGHTER_H

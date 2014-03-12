#ifndef SGATEWIDGET_H
#define SGATEWIDGET_H

#include <QWidget>
#include <QString>

#include "sgate.h"

namespace Ui {
class sGateWidget;
}

class sGateWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit sGateWidget(sGate* gate, QWidget *parent = 0);
    ~sGateWidget();
    
private:
    Ui::sGateWidget *ui;
    sGate*  m_gate;
private slots:
    void update();
};

#endif // SGATEWIDGET_H

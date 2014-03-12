#ifndef CCLIENTWIDGET_H
#define CCLIENTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QMessageBox>
#include "cwidgettxrx.h"
#include "cclient.h"


class cClient;

class cClientWidget : public QWidget
{
    Q_OBJECT
public:
    explicit cClientWidget(cClient *client, QWidget *parent=0);
    ~cClientWidget();
    void set_label_text(QString str) {m_label.setText(str);}
protected:
    cClient*     m_client;
    QHBoxLayout* m_ly;
    cWidgetTxRx  m_tx_widget;
    QPushButton  m_btn_close;
    QPushButton  m_btn_info;
    QLabel       m_label;
signals:
private slots:
    void auth_completed(bool status);
public slots:
    void tx() {m_tx_widget.tx();}
    void rx() {m_tx_widget.rx();}
    void show_clientInfo();
};

#endif // CCLIENTWIDGET_H

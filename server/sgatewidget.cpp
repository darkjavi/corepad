#include "sgatewidget.h"
#include "ui_sgatewidget.h"

sGateWidget::sGateWidget(sGate *gate, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sGateWidget)
{
    ui->setupUi(this);

    m_gate = gate;
    connect(gate,SIGNAL(rx()),ui->widget_txrx,SLOT(rx()));
    connect(gate,SIGNAL(tx()),ui->widget_txrx,SLOT(tx()));
    connect(gate,SIGNAL(newConnection()),this,SLOT(update()));
    ui->label_name->setText(gate->serverAddress().toString());
    update();
}

sGateWidget::~sGateWidget()
{
    delete ui;
}

void sGateWidget::update()
{
    QString str("Clients:");
    str.append(QString::number(m_gate->client_count()));
    str.append("A:").append(QString::number(m_gate->get_connectionAttemps()));
    str.append(" S:").append(QString::number(m_gate->get_connectionSuccess()));
    str.append(" B:").append(QString::number(m_gate->get_connectioBadauth()));
    str.append(" F:").append(QString::number(m_gate->get_connectionFailed()));
    ui->label_desc->setText(str);
}

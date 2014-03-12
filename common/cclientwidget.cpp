#include "cclientwidget.h"

cClientWidget::cClientWidget(cClient *client, QWidget *parent) :
    QWidget(parent)
{
    m_client = client;
    if(client->get_userName() != "")
    {
        m_label.setText(client->get_userName());
    }
    else
    {
        m_label.setText("Unknown");
    }
    m_ly = new QHBoxLayout(this);
    m_ly->addWidget(&m_label);
    m_ly->addWidget(&m_btn_close);
    m_ly->addWidget(&m_btn_info);
    m_ly->addWidget(&m_tx_widget);
    this->setContentsMargins(0,0,0,0);
    m_ly->setSpacing(0);
    m_btn_close.setText("Kick");
    m_btn_info.setText("info");
    connect(m_client, SIGNAL(tx()), this, SLOT(tx()));
    connect(m_client, SIGNAL(rx()), this, SLOT(rx()));
    connect(&m_btn_close,SIGNAL(clicked()),m_client,SLOT(closeSocket()));
    connect(&m_btn_info,SIGNAL(clicked()),this,SLOT(show_clientInfo()));
    connect(client,SIGNAL(login_status(bool)),this,SLOT(auth_completed(bool)));
}

cClientWidget::~cClientWidget()
{
    delete m_ly;
}

void cClientWidget::auth_completed(bool status)
{
    if(status)
    {
        m_label.setText(m_client->get_userName());
    }
    else
    {
        m_label.setText("Unauthorized");
    }
}

void cClientWidget::show_clientInfo()
{
    QMessageBox mbox(this);
    mbox.setText(m_client->info());
    mbox.exec();
}

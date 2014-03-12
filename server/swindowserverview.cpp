#include "swindowserverview.h"
#include "ui_swindowserverview.h"
#include <QtGui>
#include "../common/cclientwidget.h"
sWindowServerView::sWindowServerView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sWindowServerView)
{
    ui->setupUi(this);
    connect(&m_server,SIGNAL(client_list(QList<cClient*>&)),this,SLOT(update_clients(QList<cClient*>&)));
    //connect(&m_server,SIGNAL(tx()),ui->server_tx_widget,SLOT(tx()));
    //connect(&m_server,SIGNAL(rx()),ui->server_tx_widget,SLOT(rx()));
    connect(ui->btn_poweroff,SIGNAL(released()),&m_server,SLOT(poweroff()));
    connect(&m_server,SIGNAL(new_client(cClient*)),this,SLOT(new_client(cClient*)));
    for(int i = 0 ; i < m_server.get_gates().count() ; i++)
    {
        sGateWidget* w = new sGateWidget(m_server.get_gates()[i],ui->gates_view);
        ui->gates_view->layout()->addWidget(w);
    }

    ui->statusBar->showMessage("UP & RUNNING! :-)",5000);

}

sWindowServerView::~sWindowServerView()
{
    delete ui;
}

void sWindowServerView::update_clients(QList<cClient *> &clients)
{
    ui->list_clients->clear();
    for (int i = 0 ; i < clients.count() ; i++)
    {
        QListWidgetItem* item = new QListWidgetItem();
        cClientWidget* widget = new cClientWidget(clients[i]);
        //w->resize(100,40);
        item->setSizeHint(QSize(100,50));
        ui->list_clients->addItem(item);
        ui->list_clients->setItemWidget(item,widget);
    }
}

void sWindowServerView::new_client(cClient *n_client)
{
    QString msg("Cliente conectado: ");
    msg.append(n_client->get_userName());
    ui->statusBar->showMessage(msg,1000);
}

bool sWindowServerView::eventFilter(QObject *obj, QEvent *event)
{
//    if (obj ==  {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            qDebug() << keyEvent->key();

            switch(keyEvent->key()) {
                case Qt::Key_Enter:
                case Qt::Key_Return:
                    //sendMessage();
                return true;
            }
            return false;
        } else {
            return QObject::eventFilter(obj, event);
        }
//    } else {
//        return QObject::eventFilter(obj, event);
//    }

}

#ifndef SWINDOWSERVERVIEW_H
#define SWINDOWSERVERVIEW_H

#include <QMainWindow>
#include "sserver.h"
#include "sgatewidget.h"
namespace Ui {
class sWindowServerView;
}

class sWindowServerView : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit sWindowServerView(QWidget *parent = 0);
    ~sWindowServerView();
    
private:
    Ui::sWindowServerView *ui;
    sServer m_server;
    bool eventFilter(QObject *obj, QEvent *event);
private slots:
    void update_clients(QList<cClient*>& clients);
    void new_client(cClient* n_client);
};

#endif // SWINDOWSERVERVIEW_H

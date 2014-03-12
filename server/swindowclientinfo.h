#ifndef SWINDOWCLIENTINFO_H
#define SWINDOWCLIENTINFO_H

#include <QMainWindow>

namespace Ui {
class sWindowClientInfo;
}

class sWindowClientInfo : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit sWindowClientInfo(QWidget *parent = 0);
    ~sWindowClientInfo();
    
private:
    Ui::sWindowClientInfo *ui;
};

#endif // SWINDOWCLIENTINFO_H

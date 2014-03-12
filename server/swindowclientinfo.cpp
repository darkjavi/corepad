#include "swindowclientinfo.h"
#include "ui_swindowclientinfo.h"

sWindowClientInfo::sWindowClientInfo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sWindowClientInfo)
{
    ui->setupUi(this);
}

sWindowClientInfo::~sWindowClientInfo()
{
    delete ui;
}

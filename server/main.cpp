#include <QtGui/QApplication>
#include "swindowserverview.h"
#include "../common/cproject.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    sWindowServerView w;
    w.show();
    //cProject p("tmp","1234","test","Nobody");
    return a.exec();
}

#include "mainwindow.h"
#include <QApplication>
#include <QtNetwork>

#define HOST "pizero.local"
#define PORT 3344

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    w.show();

    w.connectTCP();
    w.sendGetAll();

    w.show();
    return a.exec();
}

#include "mainwindow.h"
#include "YyApplication.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    eApp->init();
    MainWindow w;
    w.show();
    return a.exec();
}

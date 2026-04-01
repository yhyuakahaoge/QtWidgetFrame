#include "mainwindow.h"
#include "YyMenu.h"
#include "YyWindow.h"
MainWindow::MainWindow(QWidget *parent)
{
    this->resize(800, 600);
    moveToCenter();
    setWindowIcon(QIcon(":/include/Image/Cirno.jpg"));
}



MainWindow::~MainWindow()
{

}


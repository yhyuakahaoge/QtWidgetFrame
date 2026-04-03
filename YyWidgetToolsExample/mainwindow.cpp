#include "mainwindow.h"
#include "YyMenu.h"
#include "YyWindow.h"
MainWindow::MainWindow(QWidget *parent)
{
    this->resize(800, 600);
    moveToCenter();
    setWindowIcon(QIcon(":/include/Image/Cirno.jpg"));

    setWindowPixmap(YyThemeType::Light, QPixmap(":/Resource/Image/WindowBase/Miku.png"));
    setWindowPixmap(YyThemeType::Dark, QPixmap(":/Resource/Image/WindowBase/WorldTree.jpg"));
    //setWindowMoviePath(YyThemeType::Light, ":/Resource/Image/WindowBase/Miku.gif");
    //setWindowMoviePath(YyThemeType::Dark, ":/Resource/Image/WindowBase/WorldTree.gif");
    setWindowPaintMode(YyWindowType::PaintMode::Pixmap);
}



MainWindow::~MainWindow()
{

}


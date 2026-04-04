#include "mainwindow.h"
#include "YyMenu.h"
#include "YyWindow.h"
#include "YyEventBus.h"
#include "YyStatusBar.h"
#include "YyText.h"
MainWindow::MainWindow(QWidget *parent)
{
    resize(1200, 740);
    //moveToCenter();
    setWindowIcon(QIcon(":/include/Image/Cirno.jpg"));
    setWindowTitle("YyWidgetTool");
    setWindowPixmap(YyThemeType::Light, QPixmap(":/Resource/Image/WindowBase/Miku.png"));
    setWindowPixmap(YyThemeType::Dark, QPixmap(":/Resource/Image/WindowBase/WorldTree.jpg"));
    // setWindowMoviePath(YyThemeType::Light, ":/Resource/Image/WindowBase/Miku.gif");
    // setWindowMoviePath(YyThemeType::Dark, ":/Resource/Image/WindowBase/WorldTree.gif");
    setWindowPaintMode(YyWindowType::PaintMode::Pixmap);


    _closeDialog = new YyContentDialog(this);
    connect(_closeDialog, &YyContentDialog::rightButtonClicked, this, &MainWindow::closeWindow);
    connect(_closeDialog, &YyContentDialog::middleButtonClicked, this, [=]() {
        _closeDialog->close();
        showMinimized();
    });
    this->setIsDefaultClosed(false);
    connect(this, &MainWindow::closeButtonClicked, this, [=]() {
        _closeDialog->exec();
    });

    qDebug() << "已注册的事件列表" << YyEventBus::getInstance()->getRegisteredEventsName();

    //状态栏
    YyStatusBar* statusBar = new YyStatusBar(this);
    YyText* statusText = new YyText("初始化成功！", this);
    statusText->setTextPixelSize(14);
    statusBar->addWidget(statusText);
    this->setStatusBar(statusBar);
}



MainWindow::~MainWindow()
{

}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    // if (getCurrentNavigationIndex() != 2)
    // {
    //     switch (event->button())
    //     {
    //     case Qt::BackButton:
    //     {
    //         this->setCurrentStackIndex(0);
    //         break;
    //     }
    //     case Qt::ForwardButton:
    //     {
    //         this->setCurrentStackIndex(1);
    //         break;
    //     }
    //     default:
    //     {
    //         break;
    //     }
    //     }
    // }
    YyWindow::mouseReleaseEvent(event);
}


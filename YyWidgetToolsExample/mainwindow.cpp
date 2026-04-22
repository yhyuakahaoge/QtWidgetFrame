#include "mainwindow.h"
#include "YyMenu.h"
#include "YyWindow.h"
#include "YyEventBus.h"
#include "YyStatusBar.h"
#include "YyText.h"
//#include "YyMenuBar.h"
//#include "YyNavigationRouter.h"
//#include "YyProgressBar.h"
#include "YyProgressRing.h"
#include "YySuggestBox.h"
#include "YyTheme.h"
//#include "YyToolBar.h"
#include "YyContentDialog.h"
#include "YyToolButton.h"
#include <QDebug>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QMouseEvent>
MainWindow::MainWindow(QWidget *parent)
{
    initWindow();


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

    QString testKey_1;
    QString testKey_2;
    addExpanderNode("TEST_EXPAND_NODE1", testKey_1, YyIconType::Acorn);
    addExpanderNode("TEST_EXPAND_NODE2", testKey_2, testKey_1, YyIconType::Acorn);
    addPageNode("TEST_NODE3", new QWidget(this), testKey_2, YyIconType::Acorn);
}



MainWindow::~MainWindow()
{

}

void MainWindow::initWindow()
{
    setFocusPolicy(Qt::StrongFocus);
    // setIsCentralStackedWidgetTransparent(true);
    setWindowIcon(QIcon(":/include/Image/Cirno.jpg"));
    resize(1200, 740);
    // eTheme->setThemeMode(YyThemeType::Dark);
    // setIsNavigationBarEnable(false);
    // setNavigationBarDisplayMode(YyNavigationType::Compact);
    // setWindowButtonFlag(YyAppBarType::MinimizeButtonHint, false);
    setUserInfoCardPixmap(QPixmap(":/Resource/Image/Cirno.jpg"));
    setUserInfoCardTitle("Yy Tool");
    setUserInfoCardSubTitle("666@gmail.com");
    setWindowTitle("YyWidgetTool");
    YyText* centralStack = new YyText("这是一个主窗口堆栈页面", this);
    centralStack->setFocusPolicy(Qt::StrongFocus);
    centralStack->setTextPixelSize(32);
    centralStack->setAlignment(Qt::AlignCenter);
    addCentralWidget(centralStack);
    // 窗口绘制模式
    setWindowPixmap(YyThemeType::Light, QPixmap(":/Resource/Image/WindowBase/Miku.png"));
    setWindowPixmap(YyThemeType::Dark, QPixmap(":/Resource/Image/WindowBase/WorldTree.jpg"));
    // setWindowMoviePath(YyThemeType::Light, ":/Resource/Image/WindowBase/Miku.gif");
    // setWindowMoviePath(YyThemeType::Dark, ":/Resource/Image/WindowBase/WorldTree.gif");
    setWindowPaintMode(YyWindowType::PaintMode::Pixmap);
    // 自定义AppBar菜单
    YyMenu* appBarMenu = new YyMenu(this);
    appBarMenu->setMenuItemHeight(27);
    connect(appBarMenu->addAction("跳转到一级主要堆栈"), &QAction::triggered, this, [=]() {
        //setCurrentStackIndex(0);
    });
    connect(appBarMenu->addAction("跳转到二级主要堆栈"), &QAction::triggered, this, [=]() {
        //setCurrentStackIndex(1);
    });
    connect(appBarMenu->addAction("更改页面切换特效(Scale)"), &QAction::triggered, this, [=]() {
        //setStackSwitchMode(YyWindowType::StackSwitchMode::Scale);
    });
    connect(appBarMenu->addYyIconAction(YyIconType::GearComplex, "自定义主窗口设置"), &QAction::triggered, this, [=]() {
       // navigation(_settingKey);
    });
    appBarMenu->addSeparator();
    connect(appBarMenu->addYyIconAction(YyIconType::MoonStars, "更改项目主题"), &QAction::triggered, this, [=]() {
        eTheme->setThemeMode(eTheme->getThemeMode() == YyThemeType::Light ? YyThemeType::Dark : YyThemeType::Light);
    });
    connect(appBarMenu->addAction("使用原生菜单"), &QAction::triggered, this, [=]() {
        setCustomMenu(nullptr);
    });
    setCustomMenu(appBarMenu);

    // 堆栈独立自定义窗口 具体位置为工具栏下方 导航栏右方 堆栈区上方的含有route按钮和运行时ring
    QWidget* centralCustomWidget = new QWidget(this);
    QHBoxLayout* centralCustomWidgetLayout = new QHBoxLayout(centralCustomWidget);
    centralCustomWidgetLayout->setContentsMargins(13, 15, 9, 6);
    YyToolButton* leftButton = new YyToolButton(this);
    leftButton->setYyIcon(YyIconType::AngleLeft);
    leftButton->setEnabled(false);
    // connect(leftButton, &YyToolButton::clicked, this, [=]() {
    //     YyNavigationRouter::getInstance()->navigationRouteBack();
    // });
    YyToolButton* rightButton = new YyToolButton(this);
    rightButton->setYyIcon(YyIconType::AngleRight);
    rightButton->setEnabled(false);
    // connect(rightButton, &YyToolButton::clicked, this, [=]() {
    //     YyNavigationRouter::getInstance()->navigationRouteForward();
    // });
    // connect(YyNavigationRouter::getInstance(), &YyNavigationRouter::navigationRouterStateChanged, this, [=](YyNavigationRouterType::RouteMode routeMode) {
    //     switch (routeMode)
    //     {
    //     case YyNavigationRouterType::BackValid:
    //     {
    //         leftButton->setEnabled(true);
    //         break;
    //     }
    //     case YyNavigationRouterType::BackInvalid:
    //     {
    //         leftButton->setEnabled(false);
    //         break;
    //     }
    //     case YyNavigationRouterType::ForwardValid:
    //     {
    //         rightButton->setEnabled(true);
    //         break;
    //     }
    //     case YyNavigationRouterType::ForwardInvalid:
    //     {
    //         rightButton->setEnabled(false);
    //         break;
    //     }
    //     }
    // });
    _windowSuggestBox = new YySuggestBox(this);
    _windowSuggestBox->setFixedHeight(32);
    _windowSuggestBox->setPlaceholderText("搜索关键字");
    // connect(_windowSuggestBox, &YySuggestBox::suggestionClicked, this, [=](const YySuggestBox::SuggestData& suggestData) {
    //     navigation(suggestData.getSuggestData().value("YyPageKey").toString());
    // });

    YyText* progressBusyRingText = new YyText("系统运行中", this);
    progressBusyRingText->setIsWrapAnywhere(false);
    progressBusyRingText->setTextPixelSize(15);

    YyProgressRing* progressBusyRing = new YyProgressRing(this);
    progressBusyRing->setBusyingWidth(4);
    progressBusyRing->setFixedSize(28, 28);
    progressBusyRing->setIsBusying(true);

    centralCustomWidgetLayout->addWidget(leftButton);
    centralCustomWidgetLayout->addWidget(rightButton);
    centralCustomWidgetLayout->addWidget(_windowSuggestBox);
    centralCustomWidgetLayout->addStretch();
    centralCustomWidgetLayout->addWidget(progressBusyRingText);
    centralCustomWidgetLayout->addWidget(progressBusyRing);
    setCentralCustomWidget(centralCustomWidget);
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


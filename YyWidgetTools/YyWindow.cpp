#include "YyWindow.h"

#include "YyWindowStyle.h"
#include "private/YyWindowPrivate.h"

#include <QApplication>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QMovie>
#include <QPainter>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QResizeEvent>
#include <QScreen>
#include <QStyleOption>
#include <QToolBar>
#include <QtMath>
#include <QHBoxLayout>
#include "YyTheme.h"
#include "YyApplication.h"
#include "YyEventBus.h"
#include "YyNavigationBar.h"
#include "YyCentralStackedWidget.h"
#include "YyWindowStyle.h"
#include "YyMenu.h"
Q_PROPERTY_CREATE_Q_CPP(YyWindow, int, ThemeChangeTime)
//Q_PROPERTY_CREATE_Q_CPP(YyWindow, YyWindowType::StackSwitchMode, StackSwitchMode)
Q_TAKEOVER_NATIVEEVENT_CPP(YyWindow, d_func()->_appBar);
YyWindow::YyWindow(QWidget* parent)
    : QMainWindow{parent}, d_ptr(new YyWindowPrivate())
{
    Q_D(YyWindow);
    d->q_ptr = this;
    setProperty("YyBaseClassName", "YyWindow");
    resize(1020, 680);

    d->_pThemeChangeTime = 700;
    d->_pNavigationBarDisplayMode = YyNavigationType::NavigationDisplayMode::Auto;

    // 自定义AppBar
    d->_appBar = new YyAppBar(this);
    d->_appBar->setWindowButtonFlag(YyAppBarType::NavigationButtonHint);

    connect(d->_appBar, &YyAppBar::closeButtonClicked, this, &YyWindow::closeButtonClicked);

    // 导航栏
    d->_navigationBar = new YyNavigationBar(this);

    // 导航中心堆栈窗口
    d->_navigationCenterStackedWidget = new YyCentralStackedWidget(this);
    d->_navigationCenterStackedWidget->setContentsMargins(0, 0, 0, 0);
    QWidget* navigationCentralWidget = new QWidget(this);
    navigationCentralWidget->setObjectName("YyWindowNavigationCentralWidget");
    navigationCentralWidget->setStyleSheet("#YyWindowNavigationCentralWidget{background-color:transparent;}");
    navigationCentralWidget->installEventFilter(this);
    d->_centerLayout = new QHBoxLayout(navigationCentralWidget);
    d->_centerLayout->setSpacing(5);
    d->_centerLayout->addWidget(d->_navigationBar);
    d->_centerLayout->addWidget(d->_navigationCenterStackedWidget);
    d->_centerLayout->setContentsMargins(d->_contentsMargins, 0, 0, 0);

    // 中心堆栈窗口 最外层widget
    d->_centerStackedWidget = new YyCentralStackedWidget(this);
    d->_centerStackedWidget->setIsTransparent(true);
    d->_centerStackedWidget->getContainerStackedWidget()->addWidget(navigationCentralWidget);
    setCentralWidget(d->_centerStackedWidget);
    setObjectName("YyWindow");
    setStyleSheet("#YyWindow{background-color:transparent;}");
    setStyle(new YyWindowStyle(style()));

    // 事件总线
    d->_focusEvent = new YyEvent("WMWindowClicked", "onWMWindowClickedEvent", d);
    d->_focusEvent->registerAndInit();


    // 主题变更动画
    d->_themeMode = eTheme->getThemeMode();
    // 根据主题切换按钮得到最新的_themeMode 改变主题颜色
    connect(eTheme, &YyTheme::themeModeChanged, d, &YyWindowPrivate::onThemeModeChanged);
    // 主题切换按钮 点击切换_themeMode
    connect(d->_appBar, &YyAppBar::themeChangeButtonClicked, d, &YyWindowPrivate::onThemeReadyChange);
    d->_isInitFinished = true;

    // 注册widget到_micaWidgetList中 用于更新YyMica效果
    eApp->syncWindowDisplayMode(this);
    d->_windowDisplayMode = eApp->getWindowDisplayMode();
    connect(eApp, &YyApplication::pWindowDisplayModeChanged, d, &YyWindowPrivate::onWindowDisplayModeChanged);

    d->_pWindowPaintMode = YyWindowType::PaintMode::Normal;
    d->_lightWindowPix = new QPixmap();
    d->_darkWindowPix = new QPixmap();

    d->_windowPaintMovie = new QMovie(this);
    connect(d->_windowPaintMovie, &QMovie::frameChanged, this, [=]() {
        update();
    });
}

YyWindow::~YyWindow()
{
    Q_D(YyWindow);
    eApp->syncWindowDisplayMode(this, false);
    // 会被delete两次
    //delete this->style();
    delete d->_lightWindowPix;
    delete d->_darkWindowPix;
}

//Q_PROPERTY_CREATE_Q_H(bool, IsStayTop)
void YyWindow::setIsStayTop(bool isStayTop)
{
    Q_D(YyWindow);
    d->_appBar->setIsStayTop(isStayTop);
    Q_EMIT pIsStayTopChanged();
}

bool YyWindow::getIsStayTop() const
{
    return d_ptr->_appBar->getIsStayTop();
}
//Q_PROPERTY_CREATE_Q_H(bool, IsStayTop)


//Q_PROPERTY_CREATE_Q_H(bool, isFixedSize)
void YyWindow::setIsFixedSize(bool isFixedSize)
{
    Q_D(YyWindow);
    d->_appBar->setIsFixedSize(isFixedSize);
    Q_EMIT pIsFixedSizeChanged();
}

bool YyWindow::getIsFixedSize() const
{
    return d_ptr->_appBar->getIsFixedSize();
}
//Q_PROPERTY_CREATE_Q_H(bool, isFixedSize)

//Q_PROPERTY_CREATE_Q_H(bool, isDefaultClosed)
void YyWindow::setIsDefaultClosed(bool isDefaultClosed)
{
    Q_D(YyWindow);
    d->_appBar->setIsDefaultClosed(isDefaultClosed);
    Q_EMIT pIsDefaultClosedChanged();
}

bool YyWindow::getIsDefaultClosed() const
{
    return d_ptr->_appBar->getIsDefaultClosed();
}
//Q_PROPERTY_CREATE_Q_H(bool, isDefaultClosed)

//Q_PROPERTY_CREATE_Q_H(int, appBarHeight)
void YyWindow::setAppBarHeight(int appBarHeight)
{
    Q_D(YyWindow);
    d->_appBar->setAppBarHeight(appBarHeight);
    Q_EMIT pAppBarHeightChanged();
}

int YyWindow::getAppBarHeight() const
{
    Q_D(const YyWindow);
    return d->_appBar->getAppBarHeight();
}
//Q_PROPERTY_CREATE_Q_H(int, appBarHeight)

//Q_PROPERTY_CREATE_Q_H(YyWindowType::PaintMode, WindowPaintMode)
void YyWindow::setWindowPaintMode(YyWindowType::PaintMode windowPaintMode)
{
    Q_D(YyWindow);
    if (d->_windowPaintMovie->state() == QMovie::Running)
    {
        d->_windowPaintMovie->stop();
    }
    if (windowPaintMode == YyWindowType::PaintMode::Movie)
    {
        d->_windowPaintMovie->setFileName(d->_themeMode == YyThemeType::Light ? d->_lightWindowMoviePath : d->_darkWindowMoviePath);
        d->_windowPaintMovie->start();
    }
    d->_pWindowPaintMode = windowPaintMode;
    update();
    Q_EMIT pWindowPaintModeChanged();
}

YyWindowType::PaintMode YyWindow::getWindowPaintMode() const
{
    Q_D(const YyWindow);
    return d->_pWindowPaintMode;
}
//Q_PROPERTY_CREATE_Q_H(YyWindowType::PaintMode, WindowPaintMode)


void YyWindow::moveToCenter()
{
    if (isMaximized() || isFullScreen())
    {
        return;
    }
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    auto geometry = screen()->availableGeometry();
#else
    auto geometry = qApp->screenAt(this->geometry().center())->geometry();
#endif
    setGeometry((geometry.left() + geometry.right() - width()) / 2, (geometry.top() + geometry.bottom() - height()) / 2, width(), height());
}

void YyWindow::setIsNavigationBarEnable(bool isVisible)
{
    Q_D(YyWindow);
    d->_isNavigationEnable = isVisible;
    d->_navigationBar->setVisible(isVisible);
    d->_centerLayout->setContentsMargins(isVisible ? d->_contentsMargins : 0, 0, 0, 0);
    //d->_navigationCenterStackedWidget->setIsHasRadius(isVisible);
}

bool YyWindow::getIsNavigationBarEnable() const
{
    return d_ptr->_isNavigationEnable;
}

void YyWindow::setCustomWidget(YyAppBarType::CustomArea customArea, QWidget *customWidget, QObject *hitTestObject, const QString &hitTestFunctionName)
{
    Q_D(YyWindow);
    d->_appBar->setCustomWidget(customArea, customWidget, hitTestObject, hitTestFunctionName);
    Q_EMIT customWidgetChanged();
}

void YyWindow::setWindowPixmap(YyThemeType::ThemeMode themeMode, const QPixmap &pixmap)
{
    Q_D(YyWindow);
    if (themeMode == YyThemeType::ThemeMode::Light)
    {
        *d->_lightWindowPix = pixmap;
    }
    else
    {
        *d->_darkWindowPix = pixmap;
    }
    update();
}

QPixmap YyWindow::getWindowPixmap(YyThemeType::ThemeMode themeMode) const
{
    Q_D(const YyWindow);
    return themeMode == YyThemeType::Light ? *d->_lightWindowPix : *d->_darkWindowPix;
}

void YyWindow::closeWindow()
{
    Q_D(YyWindow);
    d->_isWindowClosing = true;
    d->_appBar->closeWindow();
}

void YyWindow::setNavigationBarWidth(int navigationBarWidth)
{
    Q_D(YyWindow);
    d->_navigationBar->setNavigationBarWidth(navigationBarWidth);
    Q_EMIT pNavigationBarWidthChanged();
}

int YyWindow::getNavigationBarWidth() const
{
    Q_D(const YyWindow);
    return d->_navigationBar->getNavigationBarWidth();
}

void YyWindow::setNavigationBarDisplayMode(YyNavigationType::NavigationDisplayMode navigationBarDisplayMode)
{
    Q_D(YyWindow);
    d->_pNavigationBarDisplayMode = navigationBarDisplayMode;
    d->_currentNavigationBarDisplayMode = d->_pNavigationBarDisplayMode;
    bool isVisible = this->isVisible();
    switch (d->_pNavigationBarDisplayMode)
    {
    case YyNavigationType::Auto:
    {
        d->_doNavigationDisplayModeChange();
        break;
    }
    case YyNavigationType::Minimal:
    {
        //d->_navigationBar->setDisplayMode(YyNavigationType::Minimal, isVisible);
        break;
    }
    case YyNavigationType::Compact:
    {
        //d->_navigationBar->setDisplayMode(YyNavigationType::Compact, isVisible);
        break;
    }
    case YyNavigationType::Maximal:
    {
        //d->_navigationBar->setDisplayMode(YyNavigationType::Maximal, isVisible);
        break;
    }
    }
    Q_EMIT pNavigationBarDisplayModeChanged();
}

YyNavigationType::NavigationDisplayMode YyWindow::getNavigationBarDisplayMode() const
{
    Q_D(const YyWindow);
    return d->_pNavigationBarDisplayMode;
}

void YyWindow::setWindowMoviePath(YyThemeType::ThemeMode themeMode, const QString &moviePath)
{
    Q_D(YyWindow);
    if (themeMode == YyThemeType::ThemeMode::Light)
    {
        d->_lightWindowMoviePath = moviePath;
    }
    else
    {
        d->_darkWindowMoviePath = moviePath;
    }
    if (d->_themeMode == themeMode && d->_pWindowPaintMode == YyWindowType::PaintMode::Movie)
    {
        if (d->_windowPaintMovie->state() == QMovie::Running)
        {
            d->_windowPaintMovie->stop();
        }
        d->_windowPaintMovie->setFileName(moviePath);
        d->_windowPaintMovie->start();
    }
}

void YyWindow::setUserInfoCardVisible(bool isVisible)
{
    Q_D(YyWindow);
    d->_navigationBar->setUserInfoCardVisible(isVisible);
}

void YyWindow::setUserInfoCardPixmap(QPixmap pix)
{
    Q_D(YyWindow);
    d->_navigationBar->setUserInfoCardPixmap(pix);
}

void YyWindow::setUserInfoCardTitle(QString Title)
{
    Q_D(YyWindow);
    d->_navigationBar->setUserInfoCardTitle(Title);
}

void YyWindow::setUserInfoCardSubTitle(QString subTitle)
{
    Q_D(YyWindow);
    d->_navigationBar->setUserInfoCardSubTitle(subTitle);
}

void YyWindow::setCentralCustomWidget(QWidget *customWidget)
{
    Q_D(YyWindow);
    d->_navigationCenterStackedWidget->setCustomWidget(customWidget);
    Q_EMIT centralCustomWidgetChanged();
}

QWidget *YyWindow::getCentralCustomWidget() const
{
    Q_D(const YyWindow);
    return d->_navigationCenterStackedWidget->getCustomWidget();
}

void YyWindow::setCustomMenu(QMenu *customMenu)
{
    Q_D(YyWindow);
    d->_appBar->setCustomMenu(customMenu);
    Q_EMIT customMenuChanged();
}

QMenu *YyWindow::getCustomMenu() const
{
    Q_D(const YyWindow);
    return d->_appBar->getCustomMenu();
}

YyNavigationType::NodeResult YyWindow::addExpanderNode(const QString &expanderTitle, QString &expanderKey, YyIconType::IconName awesome) const
{
    Q_D(const YyWindow);
    return d->_navigationBar->addExpanderNode(expanderTitle, expanderKey, awesome);
}

YyNavigationType::NodeResult YyWindow::addExpanderNode(const QString &expanderTitle, QString &expanderKey, const QString &targetExpanderKey, YyIconType::IconName awesome) const
{
    Q_D(const YyWindow);
    return d->_navigationBar->addExpanderNode(expanderTitle, expanderKey, targetExpanderKey, awesome);
}

YyNavigationType::NodeResult YyWindow::addPageNode(const QString &pageTitle, QWidget *page, YyIconType::IconName awesome)
{
    Q_D(YyWindow);
    auto returnType = d->_navigationBar->addPageNode(pageTitle, page, awesome);
    if (returnType == YyNavigationType::Success)
    {
        d->_pageMetaMap.insert(page->property("YyPageKey").toString(), page->metaObject());
    }
    return returnType;
}

YyNavigationType::NodeResult YyWindow::addPageNode(const QString &pageTitle, QWidget *page, int keyPoints, YyIconType::IconName awesome)
{
    Q_D(YyWindow);
    auto returnType = d->_navigationBar->addPageNode(pageTitle, page, keyPoints, awesome);
    if (returnType == YyNavigationType::Success)
    {
        d->_pageMetaMap.insert(page->property("YyPageKey").toString(), page->metaObject());
    }
    return returnType;
}

YyNavigationType::NodeResult YyWindow::addPageNode(const QString &pageTitle, QWidget *page, const QString &targetExpanderKey, YyIconType::IconName awesome)
{
    Q_D(YyWindow);
    auto returnType = d->_navigationBar->addPageNode(pageTitle, page, targetExpanderKey, awesome);
    if (returnType == YyNavigationType::Success)
    {
        d->_pageMetaMap.insert(page->property("YyPageKey").toString(), page->metaObject());
    }
    return returnType;
}

YyNavigationType::NodeResult YyWindow::addPageNode(const QString &pageTitle, QWidget *page, const QString &targetExpanderKey, int keyPoints, YyIconType::IconName awesome)
{
    Q_D(YyWindow);
    auto returnType = d->_navigationBar->addPageNode(pageTitle, page, targetExpanderKey, keyPoints, awesome);
    if (returnType == YyNavigationType::Success)
    {
        d->_pageMetaMap.insert(page->property("YyPageKey").toString(), page->metaObject());
    }
    return returnType;
}

YyNavigationType::NodeResult YyWindow::addFooterNode(const QString &footerTitle, QString &footerKey, int keyPoints, YyIconType::IconName awesome) const
{
    Q_D(const YyWindow);
    return d->_navigationBar->addFooterNode(footerTitle, nullptr, footerKey, keyPoints, awesome);
}

YyNavigationType::NodeResult YyWindow::addFooterNode(const QString &footerTitle, QWidget *page, QString &footerKey, int keyPoints, YyIconType::IconName awesome)
{
    Q_D(YyWindow);
    auto returnType = d->_navigationBar->addFooterNode(footerTitle, page, footerKey, keyPoints, awesome);
    if (page && returnType == YyNavigationType::Success)
    {
        d->_pageMetaMap.insert(page->property("YyPageKey").toString(), page->metaObject());
    }
    return returnType;
}

YyNavigationType::NodeResult YyWindow::addCategoryNode(const QString &categoryTitle, QString &categoryKey)
{
    Q_D(const YyWindow);
    return d->_navigationBar->addCategoryNode(categoryTitle, categoryKey);
}

YyNavigationType::NodeResult YyWindow::addCategoryNode(const QString &categoryTitle, QString &categoryKey, const QString &targetExpanderKey)
{
    Q_D(const YyWindow);
    return d->_navigationBar->addCategoryNode(categoryTitle, categoryKey, targetExpanderKey);
}

void YyWindow::addCentralWidget(QWidget *centralWidget)
{
    Q_D(YyWindow);
    if (!centralWidget)
    {
        return;
    }
    d->_centerStackedWidget->getContainerStackedWidget()->addWidget(centralWidget);
}

bool YyWindow::eventFilter(QObject *watched, QEvent *event)
{
    Q_D(YyWindow);
    switch (event->type())
    {
    case QEvent::Resize:
    {
        //d->_doNavigationDisplayModeChange();
        break;
    }
    default:
    {
        break;
    }
    }
    return QMainWindow::eventFilter(watched, event);
}

QMenu *YyWindow::createPopupMenu()
{
    YyMenu* menu = nullptr;
    QList<QDockWidget*> dockwidgets = findChildren<QDockWidget*>();
    if (dockwidgets.size())
    {
        menu = new YyMenu(this);
        for (int i = 0; i < dockwidgets.size(); ++i)
        {
            QDockWidget* dockWidget = dockwidgets.at(i);
            if (dockWidget->parentWidget() == this)
            {
                menu->addAction(dockwidgets.at(i)->toggleViewAction());
            }
        }
        menu->addSeparator();
    }

    QList<QToolBar*> toolbars = findChildren<QToolBar*>();
    if (toolbars.size())
    {
        if (!menu)
        {
            menu = new YyMenu(this);
        }
        for (int i = 0; i < toolbars.size(); ++i)
        {
            QToolBar* toolBar = toolbars.at(i);
            if (toolBar->parentWidget() == this)
            {
                menu->addAction(toolbars.at(i)->toggleViewAction());
            }
        }
    }
    if (menu)
    {
        menu->setMenuItemHeight(28);
    }
    return menu;
}


void YyWindow::paintEvent(QPaintEvent* event)
{
    Q_D(YyWindow);
    QPainter painter(this);
    painter.save();
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    switch (d->_windowDisplayMode)
    {
    case YyApplicationType::Normal:
    {
        switch (d->_pWindowPaintMode)
        {
        case YyWindowType::Normal:
        {
            painter.setPen(Qt::NoPen);
            painter.setBrush(YyThemeColor(d->_themeMode, WindowBase));
            painter.drawRect(rect());
            break;
        }
        case YyWindowType::Pixmap:
        {
            QPixmap* pix = d->_themeMode == YyThemeType::Light ? d->_lightWindowPix : d->_darkWindowPix;
            qreal windowAspectRatio = (qreal)rect().width() / rect().height();
            qreal pixAspectRatio = (qreal)pix->width() / pix->height();
            int targetPixWidth, targetPixHeight;
            //居中显示且保持图片比例
            if (windowAspectRatio < pixAspectRatio)
            {
                targetPixWidth = qRound(pix->width() * windowAspectRatio / pixAspectRatio);
                targetPixHeight = pix->height();
            }
            else
            {
                targetPixWidth = pix->width();
                targetPixHeight = qRound(pix->height() * pixAspectRatio / windowAspectRatio);
            }
            painter.drawPixmap(rect(), *pix, QRect((pix->width() - targetPixWidth) / 2, (pix->height() - targetPixHeight) / 2, targetPixWidth, targetPixHeight));
            break;
        }
        case YyWindowType::Movie:
        {
            QPixmap pix = d->_windowPaintMovie->currentPixmap();
            qreal windowAspectRatio = (qreal)rect().width() / rect().height();
            qreal pixAspectRatio = (qreal)pix.width() / pix.height();
            int targetPixWidth, targetPixHeight;
            if (windowAspectRatio < pixAspectRatio)
            {
                targetPixWidth = qRound(pix.width() * windowAspectRatio / pixAspectRatio);
                targetPixHeight = pix.height();
            }
            else
            {
                targetPixWidth = pix.width();
                targetPixHeight = qRound(pix.height() * pixAspectRatio / windowAspectRatio);
            }
            painter.drawPixmap(rect(), pix, QRect((pix.width() - targetPixWidth) / 2, (pix.height() - targetPixHeight) / 2, targetPixWidth, targetPixHeight));
            break;
        }
        default:
        {
            break;
        }
        }
    }
    default:
    {
        break;
    }
    }
    painter.restore();
}


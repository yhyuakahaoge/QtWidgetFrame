#include "YyWindow.h"

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
    // 自定义AppBar
    d->_appBar = new YyAppBar(this);
    d->_appBar->setWindowButtonFlag(YyAppBarType::NavigationButtonHint);

}

YyWindow::~YyWindow()
{

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

void YyWindow::setCustomWidget(YyAppBarType::CustomArea customArea, QWidget *customWidget, QObject *hitTestObject, const QString &hitTestFunctionName)
{
    Q_D(YyWindow);
    d->_appBar->setCustomWidget(customArea, customWidget, hitTestObject, hitTestFunctionName);
    Q_EMIT customWidgetChanged();
}


#include "YyWindow.h"

#include "private/YyWindowPrivate.h"

#include "YyAppBar.h"

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
YyWindow::YyWindow(QWidget* parent)
    : QMainWindow{parent}, d_ptr(new YyWindowPrivate())
{
    Q_D(YyWindow);
    d->q_ptr = this;

    // 自定义AppBar
    d->_appBar = new YyAppBar(this);
}

YyWindow::~YyWindow()
{

}

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


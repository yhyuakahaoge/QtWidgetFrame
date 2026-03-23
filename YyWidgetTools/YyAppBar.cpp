#include "YyAppBar.h"

#include <QApplication>
#include <QDebug>
#include <QGuiApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QScreen>
#include <QTimer>
#include <QVBoxLayout>

#include "private/YyAppBarPrivate.h"

Q_PROPERTY_CREATE_Q_CPP(YyAppBar, bool, IsStayTop)
Q_PROPERTY_CREATE_Q_CPP(YyAppBar, bool, IsFixedSize)
Q_PROPERTY_CREATE_Q_CPP(YyAppBar, bool, IsDefaultClosed)
Q_PROPERTY_CREATE_Q_CPP(YyAppBar, bool, IsOnlyAllowMinAndClose)
Q_PROPERTY_CREATE_Q_CPP(YyAppBar, int, AppBarHeight)

YyAppBar::YyAppBar(QWidget *parent)
    : QWidget{parent}, d_ptr(new YyAppBarPrivate())
{

}

YyAppBar::~YyAppBar()
{

}

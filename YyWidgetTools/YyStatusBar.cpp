#include "YyStatusBar.h"

#include <QPainter>
#include <QTimer>

#include "YyStatusBarStyle.h"
YyStatusBar::YyStatusBar(QWidget* parent)
    : QStatusBar(parent)
{
    setObjectName("YyStatusBar");
    setStyleSheet("#YyStatusBar{background-color:transparent;}");
    setFixedHeight(28);
    setContentsMargins(20, 0, 0, 0);
    setStyle(new YyStatusBarStyle(style()));
}

YyStatusBar::~YyStatusBar()
{
}

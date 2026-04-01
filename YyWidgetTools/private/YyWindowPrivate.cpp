#include "YyWindowPrivate.h"

#include "YyAppBarPrivate.h"
//#include "YyApplication.h"
//#include "YyCentralStackedWidget.h"
//#include "YyNavigationBar.h"
#include "YyTheme.h"
//#include "YyThemeAnimationWidget.h"
#include "YyWindow.h"
#include <QApplication>
#include <QPropertyAnimation>
#include <QTimer>
#include <QVBoxLayout>
#include <QtMath>
YyWindowPrivate::YyWindowPrivate(QObject* parent)
    : QObject{parent}
{
}

YyWindowPrivate::~YyWindowPrivate()
{
}

#include "YyAppBarPrivate.h"

#include <QDebug>
#include <QGuiApplication>
#include <QLabel>
#include <QMenu>
#include <QPropertyAnimation>
#include <QScreen>
#include <QVBoxLayout>
#include <QWidget>
#include <QWindow>
YyAppBarPrivate::YyAppBarPrivate(QObject* parent)
    : QObject{parent}
{
}

YyAppBarPrivate::~YyAppBarPrivate()
{
}

#include "YyApplicationPrivate.h"

#include <QApplication>
#include <QEvent>
#include <QImage>
#include <QPalette>
#include <QScreen>
#include <QThread>
#include <QWidget>
#include <QtMath>

#include "YyApplication.h"
#include "YyMicaBaseInitObject.h"
#include "YyWinShadowHelper.h"
YyApplicationPrivate::YyApplicationPrivate(QObject* parent)
    : QObject{parent}
{
}

YyApplicationPrivate::~YyApplicationPrivate()
{
}

void YyApplicationPrivate::onThemeModeChanged(YyThemeType::ThemeMode themeMode)
{
    _themeMode = themeMode;
    switch (_pWindowDisplayMode)
    {
    case YyApplicationType::Normal:
    {
        break;
    }
    case YyApplicationType::YyMica:
    {
        _updateAllMicaWidget();
        break;
    }
    default:
    {
#ifdef Q_OS_WIN
        for (auto widget: _micaWidgetList)
        {
            YyWinShadowHelper::getInstance()->setWindowThemeMode(widget->winId(), _themeMode == YyThemeType::Light);
        }
#endif
        break;
    }
    }
}

bool YyApplicationPrivate::eventFilter(QObject* watched, QEvent* event)
{
    switch (event->type())
    {
    case QEvent::Show:
    {
        if (_pWindowDisplayMode == YyApplicationType::WindowDisplayMode::YyMica)
        {
            QWidget* widget = qobject_cast<QWidget*>(watched);
            if (widget)
            {
                _updateMica(widget);
            }
        }
        else if (_pWindowDisplayMode != YyApplicationType::WindowDisplayMode::Normal)
        {
#ifdef Q_OS_WIN
            QWidget* widget = qobject_cast<QWidget*>(watched);
            if (widget)
            {
                YyWinShadowHelper::getInstance()->setWindowDisplayMode(widget, _pWindowDisplayMode, _pWindowDisplayMode);
            }
#endif
        }
        break;
    }
    case QEvent::Move:
    case QEvent::Resize:
    {
        if (_pWindowDisplayMode == YyApplicationType::WindowDisplayMode::YyMica)
        {
            QWidget* widget = qobject_cast<QWidget*>(watched);
            if (widget)
            {
                _updateMica(widget);
            }
        }
        break;
    }
    case QEvent::Destroy:
    {
        QWidget* widget = qobject_cast<QWidget*>(watched);
        if (widget)
        {
            _micaWidgetList.removeOne(widget);
        }
        break;
    }
    default:
    {
        break;
    }
    }
    return QObject::eventFilter(watched, event);
}

void YyApplicationPrivate::_initMicaBaseImage(QImage img)
{
    Q_Q(YyApplication);
    if (img.isNull())
    {
        return;
    }
    QThread* initThread = new QThread();
    YyMicaBaseInitObject* initObject = new YyMicaBaseInitObject(this);
    connect(initThread, &QThread::finished, initObject, &YyMicaBaseInitObject::deleteLater);
    connect(initObject, &YyMicaBaseInitObject::initFinished, initThread, [=]() {
        Q_EMIT q->pWindowDisplayModeChanged();
        _updateAllMicaWidget();
        initThread->quit();
        initThread->wait();
        initThread->deleteLater();
    });
    initObject->moveToThread(initThread);
    initThread->start();
    connect(this, &YyApplicationPrivate::initMicaBase, initObject, &YyMicaBaseInitObject::onInitMicaBase);
    Q_EMIT initMicaBase(img);
}

QRect YyApplicationPrivate::_calculateWindowVirtualGeometry(QWidget* widget)
{
    QRect geometry = widget->geometry();
    qreal xImageRatio = 1, yImageRatio = 1;
    QRect rYytiveGeometry;
    if (qApp->screens().count() > 1)
    {
        QScreen* currentScreen = qApp->screenAt(geometry.topLeft());
        if (currentScreen)
        {
            QRect screenGeometry = currentScreen->availableGeometry();
            xImageRatio = (qreal)_lightBaseImage.width() / screenGeometry.width();
            yImageRatio = (qreal)_lightBaseImage.height() / screenGeometry.height();
            rYytiveGeometry = QRect((geometry.x() - screenGeometry.x()) * xImageRatio, (geometry.y() - screenGeometry.y()) * yImageRatio, geometry.width() * xImageRatio, geometry.height() * yImageRatio);
            return rYytiveGeometry;
        }
    }
    QRect primaryScreenGeometry = qApp->primaryScreen()->availableGeometry();
    xImageRatio = (qreal)_lightBaseImage.width() / primaryScreenGeometry.width();
    yImageRatio = (qreal)_lightBaseImage.height() / primaryScreenGeometry.height();
    rYytiveGeometry = QRect((geometry.x() - primaryScreenGeometry.x()) * xImageRatio, (geometry.y() - primaryScreenGeometry.y()) * yImageRatio, geometry.width() * xImageRatio, geometry.height() * yImageRatio);
    return rYytiveGeometry;
}

//更新云母效果
void YyApplicationPrivate::_updateMica(QWidget* widget, bool isProcessEvent)
{
    if (widget->isVisible())
    {
        QPalette palette = widget->palette();
        if (_themeMode == YyThemeType::Light)
        {
            palette.setBrush(QPalette::Window, _lightBaseImage.copy(_calculateWindowVirtualGeometry(widget)).scaled(widget->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        }
        else
        {
            palette.setBrush(QPalette::Window, _darkBaseImage.copy(_calculateWindowVirtualGeometry(widget)).scaled(widget->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        }
        widget->setPalette(palette);
        if (isProcessEvent)
        {
            QApplication::processEvents();
        }
    }
}

void YyApplicationPrivate::_updateAllMicaWidget()
{
    if (_pWindowDisplayMode == YyApplicationType::WindowDisplayMode::YyMica)
    {
        for (auto widget: _micaWidgetList)
        {
            _updateMica(widget, false);
        }
    }
}

void YyApplicationPrivate::_resetAllMicaWidget()
{
    for (auto widget: _micaWidgetList)
    {
        QPalette palette = widget->palette();
        palette.setBrush(QPalette::Window, Qt::transparent);
        widget->setPalette(palette);
    }
}

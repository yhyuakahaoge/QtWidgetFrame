#include "YyWindowPrivate.h"

#include "YyAppBarPrivate.h"
#include "YyApplication.h"
//#include "YyCentralStackedWidget.h"
#include "YyNavigationBar.h"
#include "YyTheme.h"
#include "YyThemeAnimationWidget.h"
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

void YyWindowPrivate::onWMWindowClickedEvent(QVariantMap data)
{
    YyAppBarType::WMMouseActionType actionType = data.value("WMClickType").value<YyAppBarType::WMMouseActionType>();
    //qDebug() << "【点击触发了！】进来了！actionType：" << actionType;
    if (actionType == YyAppBarType::WMLBUTTONDBLCLK || actionType == YyAppBarType::WMLBUTTONUP)
    {
        // if (YyApplication::containsCursorToItem(_navigationBar))
        // {
        //     return;
        // }
        // if (_isNavigationBarExpanded)
        // {
        //     QPropertyAnimation* navigationMoveAnimation = new QPropertyAnimation(_navigationBar, "pos");
        //     connect(navigationMoveAnimation, &QPropertyAnimation::valueChanged, this, [=]() {
        //         if (_isNavigationDisplayModeChanged)
        //         {
        //             _isNavigationBarFloat = false;
        //             _resetWindowLayout(false);
        //             navigationMoveAnimation->deletYyter();
        //         }
        //     });
        //     connect(navigationMoveAnimation, &QPropertyAnimation::finished, this, [=]() {
        //         if (!_isNavigationDisplayModeChanged)
        //         {
        //             _navigationBar->setDisplayMode(YyNavigationType::Minimal, false);
        //             _resetWindowLayout(false);
        //         }
        //         _isNavigationBarFloat = false;
        //     });
        //     navigationMoveAnimation->setEasingCurve(QEasingCurve::OutCubic);
        //     navigationMoveAnimation->setDuration(225);
        //     navigationMoveAnimation->setStartValue(_navigationBar->pos());
        //     navigationMoveAnimation->setEndValue(QPoint(-_navigationBar->width(), 0));
        //     navigationMoveAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        //     _isNavigationBarExpanded = false;
        // }
    }
}

void YyWindowPrivate::onThemeReadyChange()
{
    Q_Q(YyWindow);
    // 主题变更绘制窗口
    switch (eApp->getWindowDisplayMode())
    {
    case YyApplicationType::Normal:
    case YyApplicationType::YyMica:
    {
        _appBar->setIsOnlyAllowMinAndClose(true);
        if (!_animationWidget)
        {
            QPoint centerPos = q->mapFromGlobal(QCursor::pos());
            _animationWidget = new YyThemeAnimationWidget(q);
            connect(_animationWidget, &YyThemeAnimationWidget::animationFinished, this, [=]() {
                _appBar->setIsOnlyAllowMinAndClose(false);
                _animationWidget = nullptr;
            });
            _animationWidget->move(0, 0);
            _animationWidget->setOldWindowBackground(q->grab(q->rect()).toImage());
            if (eTheme->getThemeMode() == YyThemeType::Light)
            {
                eTheme->setThemeMode(YyThemeType::Dark);
            }
            else
            {
                eTheme->setThemeMode(YyThemeType::Light);
            }

            _animationWidget->setCenter(centerPos);
            qreal topLeftDis = _distance(centerPos, QPoint(0, 0));
            qreal topRightDis = _distance(centerPos, QPoint(q->width(), 0));
            qreal bottomLeftDis = _distance(centerPos, QPoint(0, q->height()));
            qreal bottomRightDis = _distance(centerPos, QPoint(q->width(), q->height()));
            QList<qreal> disList{topLeftDis, topRightDis, bottomLeftDis, bottomRightDis};
            std::sort(disList.begin(), disList.end());
            _animationWidget->setEndRadius(disList[3]);
            _animationWidget->resize(q->width(), q->height());
            _animationWidget->startAnimation(_pThemeChangeTime);
        }
        break;
    }
    default:
    {
        if (eTheme->getThemeMode() == YyThemeType::Light)
        {
            eTheme->setThemeMode(YyThemeType::Dark);
        }
        else
        {
            eTheme->setThemeMode(YyThemeType::Light);
        }
        break;
    }
    }

}

void YyWindowPrivate::onThemeModeChanged(YyThemeType::ThemeMode themeMode)
{
    Q_Q(YyWindow);
    _themeMode = themeMode;
    if (_pWindowPaintMode == YyWindowType::PaintMode::Movie)
    {
        if (_windowPaintMovie->state() == QMovie::Running)
        {
            _windowPaintMovie->stop();
        }
        _windowPaintMovie->setFileName(_themeMode == YyThemeType::Light ? _lightWindowMoviePath : _darkWindowMoviePath);
        _windowPaintMovie->start();
    }
    q->update();
}

void YyWindowPrivate::onWindowDisplayModeChanged()
{
    Q_Q(YyWindow);
    _windowDisplayMode = eApp->getWindowDisplayMode();
    if (_windowPaintMovie->state() == QMovie::Running)
    {
        _windowPaintMovie->stop();
    }
    if (_windowDisplayMode == YyApplicationType::WindowDisplayMode::Normal && _pWindowPaintMode == YyWindowType::Movie)
    {
        _windowPaintMovie->setFileName(_themeMode == YyThemeType::Light ? _lightWindowMoviePath : _darkWindowMoviePath);
        _windowPaintMovie->start();
    }
    q->update();
}


qreal YyWindowPrivate::_distance(QPoint point1, QPoint point2)
{
    return std::sqrt((point1.x() - point2.x()) * (point1.x() - point2.x()) + (point1.y() - point2.y()) * (point1.y() - point2.y()));
}

void YyWindowPrivate::_doNavigationDisplayModeChange()
{
    Q_Q(YyWindow);
    if (_isWindowClosing || !_isNavigationEnable || !_isInitFinished)
    {
        return;
    }
    // if (_pNavigationBarDisplayMode == YyNavigationType::Minimal)
    // {
    //     _resetWindowLayout(false);
    // }
    // if (_pNavigationBarDisplayMode == YyNavigationType::Auto)
    // {
    //     _isNavigationDisplayModeChanged = true;
    //     _isNavigationBarFloat = false;
    //     _resetWindowLayout(false);
    //     int width = q->centralWidget()->width();
    //     if (width >= 850 && _currentNavigationBarDisplayMode != YyNavigationType::Maximal)
    //     {
    //         _navigationBar->setDisplayMode(YyNavigationType::Maximal);
    //         _currentNavigationBarDisplayMode = YyNavigationType::Maximal;
    //     }
    //     else if (width >= 550 && width < 850 && _currentNavigationBarDisplayMode != YyNavigationType::Compact)
    //     {
    //         _navigationBar->setDisplayMode(YyNavigationType::Compact);
    //         _currentNavigationBarDisplayMode = YyNavigationType::Compact;
    //     }
    //     else if (width < 550 && _currentNavigationBarDisplayMode != YyNavigationType::Minimal)
    //     {
    //         _navigationBar->setDisplayMode(YyNavigationType::Minimal);
    //         _currentNavigationBarDisplayMode = YyNavigationType::Minimal;
    //         _appBar->setWindowButtonFlag(YyAppBarType::NavigationButtonHint);
    //     }
    //     _isNavigationBarExpanded = false;
    // }
}

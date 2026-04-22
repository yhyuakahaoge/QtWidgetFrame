#ifndef YYWINDOWPRIVATE_H
#define YYWINDOWPRIVATE_H

#include "YyDef.h"
#include <QLinearGradient>
#include <QMap>
#include <QMovie>
#include <QObject>

class YyWindow;
class YyAppBar;
class YyThemeAnimationWidget;
class YyEvent;
class YyNavigationBar;
class QHBoxLayout;
class YyCentralStackedWidget;
class YyWindowPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(YyWindow)
    Q_PROPERTY_CREATE_D(int, ThemeChangeTime)
    Q_PROPERTY_CREATE_D(YyNavigationType::NavigationDisplayMode, NavigationBarDisplayMode)
    Q_PROPERTY_CREATE_D(YyWindowType::PaintMode, WindowPaintMode)

public:
    explicit YyWindowPrivate(QObject* parent = nullptr);
    virtual ~YyWindowPrivate() override;
    Q_SLOT void onThemeReadyChange();
    Q_INVOKABLE void onWMWindowClickedEvent(QVariantMap data); //最小化导航栏展开时 点击客户区自动缩回动画
    Q_SLOT void onThemeModeChanged(YyThemeType::ThemeMode themeMode);
    Q_SLOT void onWindowDisplayModeChanged();


private:
    YyThemeType::ThemeMode _themeMode;
    YyApplicationType::WindowDisplayMode _windowDisplayMode;
    QMovie* _windowPaintMovie{nullptr}; //QMovie主要显示gif

    YyAppBar* _appBar{nullptr};
    YyThemeAnimationWidget* _animationWidget{nullptr};
    qreal _distance(QPoint point1, QPoint point2);

    QString _lightWindowMoviePath{""};
    QString _darkWindowMoviePath{""};
    QPixmap* _lightWindowPix;
    QPixmap* _darkWindowPix;

    bool _isWindowClosing{false};
    bool _isNavigationEnable{true};
    YyEvent* _focusEvent{nullptr};

    YyNavigationBar* _navigationBar{nullptr};
    QHBoxLayout* _centerLayout{nullptr};
    YyCentralStackedWidget* _centerStackedWidget{nullptr};
    YyCentralStackedWidget* _navigationCenterStackedWidget{nullptr};
    YyNavigationType::NavigationDisplayMode _currentNavigationBarDisplayMode{YyNavigationType::Maximal};
    QMap<QString, const QMetaObject*> _pageMetaMap;
    QMap<QString, QWidget*> _routeMap; // key__nodeKey title可以一致  value__Page
    int _centralStackTargetIndex{0};
    int _navigationTargetIndex{0};
    bool _isInitFinished{false};
    int _contentsMargins{5};
    void _doNavigationDisplayModeChange();
};

#endif // YYWINDOWPRIVATE_H

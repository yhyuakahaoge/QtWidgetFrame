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
class YyWindowPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(YyWindow)
    Q_PROPERTY_CREATE_D(int, ThemeChangeTime)
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
    YyAppBar* _appBar{nullptr};
    bool _isInitFinished{false};
    QMovie* _windowPaintMovie{nullptr}; //QMovie主要显示gif
    QString _lightWindowMoviePath{""};
    QString _darkWindowMoviePath{""};
    QPixmap* _lightWindowPix;
    QPixmap* _darkWindowPix;
    YyThemeAnimationWidget* _animationWidget{nullptr};
    qreal _distance(QPoint point1, QPoint point2);
    bool _isWindowClosing{false};
    YyEvent* _focusEvent{nullptr};
};

#endif // YYWINDOWPRIVATE_H

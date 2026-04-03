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
class YyWindowPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(YyWindow)
    Q_PROPERTY_CREATE_D(int, ThemeChangeTime)
    Q_PROPERTY_CREATE_D(YyWindowType::PaintMode, WindowPaintMode)
public:
    explicit YyWindowPrivate(QObject* parent = nullptr);
    Q_SLOT void onThemeReadyChange();
    Q_SLOT void onThemeModeChanged(YyThemeType::ThemeMode themeMode);
    Q_SLOT void onWindowDisplayModeChanged();
    virtual ~YyWindowPrivate() override;

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
};

#endif // YYWINDOWPRIVATE_H

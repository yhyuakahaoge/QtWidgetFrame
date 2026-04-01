#ifndef YYWINDOWPRIVATE_H
#define YYWINDOWPRIVATE_H

#include "YyDef.h"
#include <QLinearGradient>
#include <QMap>
#include <QMovie>
#include <QObject>

class YyWindow;
class YyAppBar;
class YyWindowPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(YyWindow)
    Q_PROPERTY_CREATE_D(int, ThemeChangeTime)
    Q_PROPERTY_CREATE_D(YyWindowType::PaintMode, WindowPaintMode)
public:
    explicit YyWindowPrivate(QObject* parent = nullptr);
    virtual ~YyWindowPrivate() override;

private:
    YyAppBar* _appBar{nullptr};

    QMovie* _windowPaintMovie{nullptr};
    YyThemeType::ThemeMode _themeMode;
    QString _lightWindowMoviePath{""};
    QString _darkWindowMoviePath{""};
};

#endif // YYWINDOWPRIVATE_H

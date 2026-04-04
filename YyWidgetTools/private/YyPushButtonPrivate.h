#ifndef YyPUSHBUTTONPRIVATE_H
#define YyPUSHBUTTONPRIVATE_H

#include <QColor>
#include <QObject>

#include "YyDef.h"
class YyPushButton;
class YyPushButtonPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(YyPushButton)
    Q_PROPERTY_CREATE_D(int, BorderRadius)
    Q_PROPERTY_CREATE_D(QColor, LightDefaultColor)
    Q_PROPERTY_CREATE_D(QColor, DarkDefaultColor)
    Q_PROPERTY_CREATE_D(QColor, LightHoverColor)
    Q_PROPERTY_CREATE_D(QColor, DarkHoverColor)
    Q_PROPERTY_CREATE_D(QColor, LightPressColor)
    Q_PROPERTY_CREATE_D(QColor, DarkPressColor)
public:
    explicit YyPushButtonPrivate(QObject* parent = nullptr);
    ~YyPushButtonPrivate();

private:
    QColor _lightTextColor;
    QColor _darkTextColor;
    bool _isPressed{false};
    int _shadowBorderWidth{3};
    YyThemeType::ThemeMode _themeMode;
};

#endif // YyPUSHBUTTONPRIVATE_H

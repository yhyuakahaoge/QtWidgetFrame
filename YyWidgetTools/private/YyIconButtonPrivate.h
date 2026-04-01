#ifndef YyICONBUTTONPRIVATE_H
#define YyICONBUTTONPRIVATE_H

#include <QColor>
#include <QObject>
#include <QPixmap>

#include "YyDef.h"
class YyIconButton;
class YyIconButtonPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(YyIconButton)
    Q_PROPERTY_CREATE_D(int, BorderRadius)
    Q_PROPERTY_CREATE_D(qreal, Opacity);
    Q_PROPERTY_CREATE_D(YyIconType::IconName, Awesome)
    Q_PROPERTY_CREATE_D(QColor, LightHoverColor);
    Q_PROPERTY_CREATE_D(QColor, DarkHoverColor);
    Q_PROPERTY_CREATE_D(QColor, LightIconColor);
    Q_PROPERTY_CREATE_D(QColor, DarkIconColor);
    Q_PROPERTY_CREATE_D(QColor, LightHoverIconColor);
    Q_PROPERTY_CREATE_D(QColor, DarkHoverIconColor);
    Q_PROPERTY_CREATE_D(bool, IsSelected);
    Q_PROPERTY_CREATE(int, HoverAlpha)
public:
    explicit YyIconButtonPrivate(QObject* parent = nullptr);
    ~YyIconButtonPrivate();

private:
    QPixmap _iconPix;
    bool _isAlphaAnimationFinished{true};
    YyThemeType::ThemeMode _themeMode;
};

#endif // YyICONBUTTONPRIVATE_H

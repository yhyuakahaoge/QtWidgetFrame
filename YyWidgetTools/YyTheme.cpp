#include "YyTheme.h"

#include <QPainter>
#include <QPainterPath>

#include "YyThemePrivate.h"
Q_SINGLETON_CREATE_CPP(YyTheme)
YyTheme::YyTheme(QObject* parent)
    : QObject{parent}, d_ptr(new YyThemePrivate())
{
    Q_D(YyTheme);
    d->q_ptr = this;
    d->_initThemeColor();
}

YyTheme::~YyTheme()
{
}

void YyTheme::setThemeMode(YyThemeType::ThemeMode themeMode)
{
    Q_D(YyTheme);
    d->_themeMode = themeMode;
    Q_EMIT themeModeChanged(d->_themeMode);
}

YyThemeType::ThemeMode YyTheme::getThemeMode() const
{
    Q_D(const YyTheme);
    return d->_themeMode;
}

void YyTheme::drawEffectShadow(QPainter* painter, QRect widgetRect, int shadowBorderWidth, int borderRadius)
{
    Q_D(YyTheme);
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing);
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    QColor color = d->_themeMode == YyThemeType::Light ? QColor(0x70, 0x70, 0x70) : QColor(0x9C, 0x9B, 0x9E);
    for (int i = 0; i < shadowBorderWidth; i++)
    {
        path.addRoundedRect(widgetRect.x() + shadowBorderWidth - i, widgetRect.y() + shadowBorderWidth - i, widgetRect.width() - (shadowBorderWidth - i) * 2, widgetRect.height() - (shadowBorderWidth - i) * 2, borderRadius + i, borderRadius + i);
        int alpha = 1 * (shadowBorderWidth - i + 1);
        color.setAlpha(alpha > 255 ? 255 : alpha);
        painter->setPen(color);
        painter->drawPath(path);
    }
    painter->restore();
}

void YyTheme::setThemeColor(YyThemeType::ThemeMode themeMode, YyThemeType::ThemeColor themeColor, QColor newColor)
{
    Q_D(YyTheme);
    if (themeMode == YyThemeType::Light)
    {
        d->_lightThemeColorList[themeColor] = newColor;
    }
    else
    {
        d->_darkThemeColorList[themeColor] = newColor;
    }
}

const QColor& YyTheme::getThemeColor(YyThemeType::ThemeMode themeMode, YyThemeType::ThemeColor themeColor)
{
    Q_D(YyTheme);
    if (themeMode == YyThemeType::Light)
    {
        return d->_lightThemeColorList[themeColor];
    }
    else
    {
        return d->_darkThemeColorList[themeColor];
    }
}

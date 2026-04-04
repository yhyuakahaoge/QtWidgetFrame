#include "YyPushButton.h"

#include <QPainter>
#include <QPainterPath>

#include "YyTheme.h"
#include "private/YyPushButtonPrivate.h"
Q_PROPERTY_CREATE_Q_CPP(YyPushButton, int, BorderRadius)
Q_PROPERTY_CREATE_Q_CPP(YyPushButton, QColor, LightDefaultColor)
Q_PROPERTY_CREATE_Q_CPP(YyPushButton, QColor, DarkDefaultColor)
Q_PROPERTY_CREATE_Q_CPP(YyPushButton, QColor, LightHoverColor)
Q_PROPERTY_CREATE_Q_CPP(YyPushButton, QColor, DarkHoverColor)
Q_PROPERTY_CREATE_Q_CPP(YyPushButton, QColor, LightPressColor)
Q_PROPERTY_CREATE_Q_CPP(YyPushButton, QColor, DarkPressColor)
YyPushButton::YyPushButton(QWidget* parent)
    : QPushButton(parent), d_ptr(new YyPushButtonPrivate())
{
    Q_D(YyPushButton);
    d->q_ptr = this;
    d->_pBorderRadius = 3;
    d->_themeMode = eTheme->getThemeMode();
    d->_pLightDefaultColor = YyThemeColor(YyThemeType::Light, BasicBase);
    d->_pDarkDefaultColor = YyThemeColor(YyThemeType::Dark, BasicBase);
    d->_pLightHoverColor = YyThemeColor(YyThemeType::Light, BasicHover);
    d->_pDarkHoverColor = YyThemeColor(YyThemeType::Dark, BasicHover);
    d->_pLightPressColor = YyThemeColor(YyThemeType::Light, BasicPress);
    d->_pDarkPressColor = YyThemeColor(YyThemeType::Dark, BasicPress);
    d->_lightTextColor = YyThemeColor(YyThemeType::Light, BasicText);
    d->_darkTextColor = YyThemeColor(YyThemeType::Dark, BasicText);
    setMouseTracking(true);
    setFixedHeight(38);
    QFont font = this->font();
    font.setPixelSize(15);
    setFont(font);
    setObjectName("YyPushButton");
    setStyleSheet("#YyPushButton{background-color:transparent;}");
    connect(eTheme, &YyTheme::themeModeChanged, this, [=](YyThemeType::ThemeMode themeMode) {
        d->_themeMode = themeMode;
    });
}

YyPushButton::YyPushButton(QString text, QWidget* parent)
    : YyPushButton(parent)
{
    setText(text);
}

YyPushButton::~YyPushButton()
{
}

void YyPushButton::setLightTextColor(QColor color)
{
    Q_D(YyPushButton);
    d->_lightTextColor = color;
}

QColor YyPushButton::getLightTextColor() const
{
    Q_D(const YyPushButton);
    return d->_lightTextColor;
}

void YyPushButton::setDarkTextColor(QColor color)
{
    Q_D(YyPushButton);
    d->_darkTextColor = color;
}

QColor YyPushButton::getDarkTextColor() const
{
    Q_D(const YyPushButton);
    return d->_darkTextColor;
}

void YyPushButton::mousePressEvent(QMouseEvent* event)
{
    Q_D(YyPushButton);
    d->_isPressed = true;
    QPushButton::mousePressEvent(event);
}

void YyPushButton::mouseReleaseEvent(QMouseEvent* event)
{
    Q_D(YyPushButton);
    d->_isPressed = false;
    QPushButton::mouseReleaseEvent(event);
}

void YyPushButton::paintEvent(QPaintEvent* event)
{
    Q_D(YyPushButton);
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing | QPainter::TextAntialiasing);
    // 高性能阴影
    eTheme->drawEffectShadow(&painter, rect(), d->_shadowBorderWidth, d->_pBorderRadius);

    // 背景绘制
    painter.save();
    QRect foregroundRect(d->_shadowBorderWidth, d->_shadowBorderWidth, width() - 2 * (d->_shadowBorderWidth), height() - 2 * d->_shadowBorderWidth);
    if (d->_themeMode == YyThemeType::Light)
    {
        painter.setPen(YyThemeColor(YyThemeType::Light, BasicBorder));
        painter.setBrush(isEnabled() ? d->_isPressed ? d->_pLightPressColor : (underMouse() ? d->_pLightHoverColor : d->_pLightDefaultColor) : YyThemeColor(d->_themeMode, BasicDisable));
    }
    else
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(isEnabled() ? d->_isPressed ? d->_pDarkPressColor : (underMouse() ? d->_pDarkHoverColor : d->_pDarkDefaultColor) : YyThemeColor(d->_themeMode, BasicDisable));
    }
    painter.drawRoundedRect(foregroundRect, d->_pBorderRadius, d->_pBorderRadius);
    // 底边线绘制
    if (!d->_isPressed)
    {
        painter.setPen(YyThemeColor(d->_themeMode, BasicBaseLine));
        painter.drawLine(foregroundRect.x() + d->_pBorderRadius, height() - d->_shadowBorderWidth, foregroundRect.width(), height() - d->_shadowBorderWidth);
    }
    //文字绘制
    painter.setPen(isEnabled() ? d->_themeMode == YyThemeType::Light ? d->_lightTextColor : d->_darkTextColor : YyThemeColor(d->_themeMode, BasicTextDisable));
    painter.drawText(foregroundRect, Qt::AlignCenter, text());
    painter.restore();
}

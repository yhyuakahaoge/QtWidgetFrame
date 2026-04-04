#ifndef YySTATUSBARSTYLE_H
#define YySTATUSBARSTYLE_H

#include <QProxyStyle>

#include "YyDef.h"
class YyStatusBarStyle : public QProxyStyle
{
    Q_OBJECT
public:
    explicit YyStatusBarStyle(QStyle* style = nullptr);
    virtual ~YyStatusBarStyle();
    virtual void drawPrimitive(PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget = nullptr) const override;
    virtual void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget = nullptr) const override;
    virtual QSize sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& size, const QWidget* widget) const override;
    virtual int pixelMetric(PixelMetric metric, const QStyleOption* option = nullptr, const QWidget* widget = nullptr) const override;

private:
    YyThemeType::ThemeMode _themeMode;
};

#endif // YySTATUSBARSTYLE_H

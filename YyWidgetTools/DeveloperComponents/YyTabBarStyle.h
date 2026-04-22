#ifndef YyTABBARSTYLE_H
#define YyTABBARSTYLE_H

#include <QProxyStyle>

#include "YyDef.h"
class YyTabBarStyle : public QProxyStyle
{
    Q_OBJECT
    Q_PRIVATE_CREATE(QSize, TabSize)
public:
    explicit YyTabBarStyle(QStyle* style = nullptr);
    virtual ~YyTabBarStyle() override;
    virtual void drawPrimitive(QStyle::PrimitiveElement pe, const QStyleOption* opt, QPainter* p, const QWidget* w) const override;
    virtual void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget = nullptr) const override;
    virtual QSize sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& size, const QWidget* widget) const override;
    virtual QRect subElementRect(SubElement element, const QStyleOption* option, const QWidget* widget) const override;

private:
    YyThemeType::ThemeMode _themeMode;
};

#endif // YyTABBARSTYLE_H

#ifndef YySCROLLBARSTYLE_H
#define YySCROLLBARSTYLE_H
#include <QProxyStyle>

#include "YyDef.h"
class YyScrollBar;
class YyScrollBarStyle : public QProxyStyle
{
    Q_OBJECT
    Q_PRIVATE_CREATE(bool, IsExpand)
    Q_PROPERTY_CREATE(qreal, Opacity)
    Q_PROPERTY_CREATE(qreal, SliderExtent)
    Q_PRIVATE_CREATE(YyScrollBar*, ScrollBar)
public:
    explicit YyScrollBarStyle(QStyle* style = nullptr);
    ~YyScrollBarStyle();
    virtual void drawComplexControl(ComplexControl control, const QStyleOptionComplex* option, QPainter* painter, const QWidget* widget = nullptr) const override;
    virtual int pixelMetric(PixelMetric metric, const QStyleOption* option = nullptr, const QWidget* widget = nullptr) const override;
    virtual int styleHint(StyleHint hint, const QStyleOption* option = nullptr, const QWidget* widget = nullptr, QStyleHintReturn* returnData = nullptr) const override;
    void startExpandAnimation(bool isExpand);

private:
    YyThemeType::ThemeMode _themeMode;
    qreal _sliderMargin{2.5};
    int _scrollBarExtent{10};
};

#endif // YySCROLLBARSTYLE_H

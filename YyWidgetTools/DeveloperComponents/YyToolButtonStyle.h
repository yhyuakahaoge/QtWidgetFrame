#ifndef YyTOOLBUTTONSTYLE_H
#define YyTOOLBUTTONSTYLE_H

#include <QProxyStyle>

#include "YyDef.h"
class QStyleOptionToolButton;
class YyToolButtonStyle : public QProxyStyle
{
    Q_OBJECT
    Q_PRIVATE_CREATE(bool, IsTransparent)
    Q_PRIVATE_CREATE(int, BorderRadius)
    Q_PROPERTY_CREATE(qreal, ExpandIconRotate)
    Q_PRIVATE_CREATE(bool, IsSelected);

public:
    explicit YyToolButtonStyle(QStyle* style = nullptr);
    ~YyToolButtonStyle();
    virtual void drawComplexControl(ComplexControl control, const QStyleOptionComplex* option, QPainter* painter, const QWidget* widget = nullptr) const override;
    virtual QSize sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& size, const QWidget* widget) const override;

private:
    YyThemeType::ThemeMode _themeMode;
    int _contentMargin{6};
    int _hasMenuIndicatorWidth{30};
    void _drawIndicator(QPainter* painter, const QStyleOptionToolButton* bopt, const QWidget* widget) const;
    void _drawIcon(QPainter* painter, QRectF iconRect, const QStyleOptionToolButton* bopt, const QWidget* widget) const;
    void _drawText(QPainter* painter, QRect contentRect, const QStyleOptionToolButton* bopt) const;
    qreal _calculateExpandIndicatorWidth(const QStyleOptionToolButton* bopt, QPainter* painter) const;
};

#endif // YyTOOLBUTTONSTYLE_H

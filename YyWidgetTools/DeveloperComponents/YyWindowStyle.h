#ifndef YyWINDOWSTYLE_H
#define YyWINDOWSTYLE_H

#include <QProxyStyle>

#include "YyDef.h"
class YyWindowStyle : public QProxyStyle
{
    Q_OBJECT
public:
    explicit YyWindowStyle(QStyle* style = nullptr);
    ~YyWindowStyle();
    void drawPrimitive(PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget = nullptr) const override;
    void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget = nullptr) const override;

private:
    YyThemeType::ThemeMode _themeMode;
};

#endif // YyWINDOWSTYLE_H

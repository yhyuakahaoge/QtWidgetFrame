#ifndef YyICONBUTTON_H
#define YyICONBUTTON_H

#include <QPushButton>

#include "YyDef.h"
#include "YyProperty.h"
class YyIconButtonPrivate;
class Yy_EXPORT YyIconButton : public QPushButton
{
    Q_OBJECT
    Q_Q_CREATE(YyIconButton)
    Q_PROPERTY_CREATE_Q_H(int, BorderRadius)
    Q_PROPERTY_CREATE_Q_H(qreal, Opacity);
    Q_PROPERTY_CREATE_Q_H(QColor, LightHoverColor);
    Q_PROPERTY_CREATE_Q_H(QColor, DarkHoverColor);
    Q_PROPERTY_CREATE_Q_H(QColor, LightIconColor);
    Q_PROPERTY_CREATE_Q_H(QColor, DarkIconColor);
    Q_PROPERTY_CREATE_Q_H(QColor, LightHoverIconColor);
    Q_PROPERTY_CREATE_Q_H(QColor, DarkHoverIconColor);
    Q_PROPERTY_CREATE_Q_H(bool, IsSelected);

public:
    YyIconButton(QPixmap pix, QWidget* parent = nullptr);
    YyIconButton(YyIconType::IconName awesome, QWidget* parent = nullptr);
    YyIconButton(YyIconType::IconName awesome, int pixelSize, QWidget* parent = nullptr);
    YyIconButton(YyIconType::IconName awesome, int pixelSize, int fixedWidth, int fixedHeight, QWidget* parent = nullptr);
    ~YyIconButton();
    void setAwesome(YyIconType::IconName awesome);
    YyIconType::IconName getAwesome() const;

    void setPixmap(QPixmap pix);

protected:
    virtual bool event(QEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;
};

#endif // YyICONBUTTON_H

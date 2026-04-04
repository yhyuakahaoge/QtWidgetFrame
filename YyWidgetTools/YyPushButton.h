#ifndef YyPUSHBUTTON_H
#define YyPUSHBUTTON_H

#include <QPushButton>

#include "YyProperty.h"
class YyPushButtonPrivate;
class Yy_EXPORT YyPushButton : public QPushButton
{
    Q_OBJECT
    Q_Q_CREATE(YyPushButton)
    Q_PROPERTY_CREATE_Q_H(int, BorderRadius)
    Q_PROPERTY_CREATE_Q_H(QColor, LightDefaultColor)
    Q_PROPERTY_CREATE_Q_H(QColor, DarkDefaultColor)
    Q_PROPERTY_CREATE_Q_H(QColor, LightHoverColor)
    Q_PROPERTY_CREATE_Q_H(QColor, DarkHoverColor)
    Q_PROPERTY_CREATE_Q_H(QColor, LightPressColor)
    Q_PROPERTY_CREATE_Q_H(QColor, DarkPressColor)
public:
    explicit YyPushButton(QWidget* parent = nullptr);
    explicit YyPushButton(QString text, QWidget* parent = nullptr);
    ~YyPushButton();

    void setLightTextColor(QColor color);
    QColor getLightTextColor() const;

    void setDarkTextColor(QColor color);
    QColor getDarkTextColor() const;

protected:
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;
};

#endif // YyPUSHBUTTON_H

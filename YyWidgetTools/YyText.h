#ifndef YyTEXT_H
#define YyTEXT_H

#include <QLabel>

#include "YyDef.h"
#include "YyProperty.h"
class YyTextPrivate;
class Yy_EXPORT YyText : public QLabel
{
    Q_OBJECT
    Q_Q_CREATE(YyText)
    Q_PROPERTY_CREATE_Q_H(bool, IsWrapAnywhere)
    Q_PROPERTY_CREATE_Q_H(int, TextPixelSize)
    Q_PROPERTY_CREATE_Q_H(int, TextPointSize)
    Q_PROPERTY_CREATE_Q_H(YyTextType::TextStyle, TextStyle)
    Q_PROPERTY_CREATE_Q_H(YyIconType::IconName, YyIcon)
public:
    explicit YyText(QWidget* parent = nullptr);
    explicit YyText(QString text, QWidget* parent = nullptr);
    explicit YyText(QString text, int pixelSize, QWidget* parent = nullptr);
    ~YyText() override;

protected:
    virtual void paintEvent(QPaintEvent* event) override;
};

#endif // YyTEXT_H

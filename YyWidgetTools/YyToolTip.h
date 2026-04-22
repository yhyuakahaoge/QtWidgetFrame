#ifndef YyTOOLTIP_H
#define YyTOOLTIP_H

#include <QWidget>

#include "YyProperty.h"
class YyToolTipPrivate;
class Yy_EXPORT YyToolTip : public QWidget
{
    Q_OBJECT
    Q_Q_CREATE(YyToolTip)
    Q_PROPERTY_CREATE_Q_H(int, BorderRadius)
    Q_PROPERTY_CREATE_Q_H(int, DisplayMsec)
    Q_PROPERTY_CREATE_Q_H(int, ShowDelayMsec)
    Q_PROPERTY_CREATE_Q_H(int, HideDelayMsec)
    Q_PROPERTY_CREATE_Q_H(QString, ToolTip)
    Q_PROPERTY_CREATE_Q_H(QWidget*, CustomWidget)
public:
    explicit YyToolTip(QWidget* parent = nullptr);
    ~YyToolTip() override;

    void updatePos();

protected:
    virtual void paintEvent(QPaintEvent* event);
};

#endif // YyTOOLTIP_H

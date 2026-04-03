#ifndef YyTHEMEANIMATIONWIDGET_H
#define YyTHEMEANIMATIONWIDGET_H

#include <QWidget>

#include "YyProperty.h"
class YyThemeAnimationWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY_CREATE(qreal, Radius)
    Q_PROPERTY_CREATE(qreal, EndRadius)
    Q_PROPERTY_CREATE(QPoint, Center)
    Q_PROPERTY_CREATE(QImage, OldWindowBackground)
public:
    explicit YyThemeAnimationWidget(QWidget* parent = nullptr);
    ~YyThemeAnimationWidget() override;
    void startAnimation(int msec);
Q_SIGNALS:
    Q_SIGNAL void animationFinished();

protected:
    virtual void paintEvent(QPaintEvent* event) override;
};

#endif // YyTHEMEANIMATIONWIDGET_H

#ifndef YyMASKWIDGET_H
#define YyMASKWIDGET_H

#include <QWidget>

#include "YyProperty.h"
class YyMaskWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY_CREATE(int, MaskAlpha)
public:
    explicit YyMaskWidget(QWidget* parent = nullptr);
    ~YyMaskWidget();
    void doMaskAnimation(int endValue);

protected:
    virtual void paintEvent(QPaintEvent* event) override;
};

#endif // YyMASKWIDGET_H

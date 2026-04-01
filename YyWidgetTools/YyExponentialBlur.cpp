#include "YyExponentialBlur.h"

#include <QPainter>
#include <QPixmap>

#include "YyExponentialBlurPrivate.h"
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <cmath>
#endif
Q_SINGLETON_CREATE_CPP(YyExponentialBlur)
YyExponentialBlur::YyExponentialBlur(QObject* parent)
    : QObject{parent}, d_ptr(new YyExponentialBlurPrivate())
{
    Q_D(YyExponentialBlur);
    d->q_ptr = this;
}

YyExponentialBlur::~YyExponentialBlur()
{
}

QPixmap YyExponentialBlur::doExponentialBlur(QImage img, const quint16& blurRadius)
{
    QImage shadowImage = img.convertToFormat(QImage::Format_ARGB32);
    YyExponentialBlur::getInstance()->d_ptr->_drawExponentialBlur(shadowImage, blurRadius);
    return QPixmap::fromImage(shadowImage);
}

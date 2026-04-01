#ifndef YyEXPONENTIALBLUR_H
#define YyEXPONENTIALBLUR_H

#include <QObject>

#include "YyProperty.h"
#include "YySingleton.h"

class YyExponentialBlurPrivate;
class Yy_EXPORT YyExponentialBlur : public QObject
{
    Q_OBJECT
    Q_SINGLETON_CREATE_H(YyExponentialBlur)
    Q_Q_CREATE(YyExponentialBlur)
private:
    explicit YyExponentialBlur(QObject* parent = nullptr);
    ~YyExponentialBlur();

public:
    static QPixmap doExponentialBlur(QImage img, const quint16& blurRadius);
};

#endif // YyEXPONENTIALBLUR_H

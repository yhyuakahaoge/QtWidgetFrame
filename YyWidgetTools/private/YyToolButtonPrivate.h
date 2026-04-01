#ifndef YyTOOLBUTTONPRIVATE_H
#define YyTOOLBUTTONPRIVATE_H

#include <QObject>

#include "YyProperty.h"
class YyToolButton;
class YyToolButtonStyle;
class YyToolButtonPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(YyToolButton)
public:
    explicit YyToolButtonPrivate(QObject* parent = nullptr);
    ~YyToolButtonPrivate();

private:
    YyToolButtonStyle* _toolButtonStyle{nullptr};
};

#endif // YyTOOLBUTTONPRIVATE_H

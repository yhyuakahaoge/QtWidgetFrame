#ifndef YyMENUPRIVATE_H
#define YyMENUPRIVATE_H

#include <QObject>
#include <QPixmap>
#include <QPoint>

#include "YyProperty.h"
class YyMenu;
class YyMenuStyle;
class YyMenuPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(YyMenu)
    Q_PROPERTY_CREATE(int, AnimationImagePosY)
public:
    explicit YyMenuPrivate(QObject* parent = nullptr);
    ~YyMenuPrivate() override;

private:
    QPixmap _animationPix;
    bool _isCloseAnimation{false};
    QPoint _mousePressPoint;
    YyMenuStyle* _menuStyle{nullptr};
};

#endif // YyMENUPRIVATE_H

#include "YyToolButton.h"

#include <QApplication>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QPropertyAnimation>

#include "DeveloperComponents/YyToolButtonStyle.h"
#include "YyIcon.h"
#include "YyMenu.h"
#include "YyToolButtonPrivate.h"
YyToolButton::YyToolButton(QWidget* parent)
    : QToolButton(parent), d_ptr(new YyToolButtonPrivate())
{
    Q_D(YyToolButton);
    d->q_ptr = this;
    setIconSize(QSize(22, 22));
    setPopupMode(QToolButton::InstantPopup);
    d->_toolButtonStyle = new YyToolButtonStyle(style());
    setStyle(d->_toolButtonStyle);
}

YyToolButton::~YyToolButton()
{
    Q_D(YyToolButton);
    delete d->_toolButtonStyle;
}

void YyToolButton::setBorderRadius(int borderRadius)
{
    Q_D(YyToolButton);
    d->_toolButtonStyle->setBorderRadius(borderRadius);
    Q_EMIT pBorderRadiusChanged();
}

int YyToolButton::getBorderRadius() const
{
    Q_D(const YyToolButton);
    return d->_toolButtonStyle->getBorderRadius();
}

void YyToolButton::setIsSelected(bool isSelected)
{
    Q_D(YyToolButton);
    d->_toolButtonStyle->setIsSelected(isSelected);
    Q_EMIT pIsSelectedChanged();
}

bool YyToolButton::getIsSelected() const
{
    Q_D(const YyToolButton);
    return d->_toolButtonStyle->getIsSelected();
}

void YyToolButton::setIsTransparent(bool isTransparent)
{
    Q_D(YyToolButton);
    d->_toolButtonStyle->setIsTransparent(isTransparent);
    update();
}

bool YyToolButton::getIsTransparent() const
{
    Q_D(const YyToolButton);
    return d->_toolButtonStyle->getIsTransparent();
}

void YyToolButton::setMenu(YyMenu* menu)
{
    if (!menu || menu == this->menu())
    {
        return;
    }
    menu->setMenuItemHeight(27);
    QToolButton::setMenu(menu);
    menu->installEventFilter(this);
}

void YyToolButton::setYyIcon(YyIconType::IconName icon)
{
    setProperty("YyIconType", QChar((unsigned short)icon));
    setIcon(YyIcon::getInstance()->getYyIcon(YyIconType::Broom, 1));
}

void YyToolButton::setYyIcon(YyIconType::IconName icon, int rotate)
{
    setYyIcon(icon);
    setProperty("YyIconRotate", rotate);
}

bool YyToolButton::eventFilter(QObject* watched, QEvent* event)
{
    Q_D(YyToolButton);
    if (watched == menu())
    {
        switch (event->type())
        {
        case QEvent::Show:
        {
            //指示器动画
            QPropertyAnimation* rotateAnimation = new QPropertyAnimation(d->_toolButtonStyle, "pExpandIconRotate");
            connect(rotateAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
                update();
            });
            rotateAnimation->setDuration(300);
            rotateAnimation->setEasingCurve(QEasingCurve::InOutSine);
            rotateAnimation->setStartValue(d->_toolButtonStyle->getExpandIconRotate());
            rotateAnimation->setEndValue(-180);
            rotateAnimation->start(QAbstractAnimation::DeleteWhenStopped);
            break;
        }
        case QEvent::Hide:
        {
            //指示器动画
            QPropertyAnimation* rotateAnimation = new QPropertyAnimation(d->_toolButtonStyle, "pExpandIconRotate");
            connect(rotateAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
                update();
            });
            rotateAnimation->setDuration(300);
            rotateAnimation->setEasingCurve(QEasingCurve::InOutSine);
            rotateAnimation->setStartValue(d->_toolButtonStyle->getExpandIconRotate());
            rotateAnimation->setEndValue(0);
            rotateAnimation->start(QAbstractAnimation::DeleteWhenStopped);
            QMouseEvent focusEvent(QEvent::MouseButtonPress, QPoint(-1, -1), QPoint(-1, -1), Qt::NoButton, Qt::NoButton, Qt::NoModifier);
            QApplication::sendEvent(parentWidget(), &focusEvent);
            break;
        }
        default:
        {
            break;
        }
        }
    }
    return QObject::eventFilter(watched, event);
}

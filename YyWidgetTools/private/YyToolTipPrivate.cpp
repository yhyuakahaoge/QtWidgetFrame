#include "YyToolTipPrivate.h"

#include <QEvent>
#include <QPropertyAnimation>
#include <QTimer>

#include "YyToolTip.h"
YyToolTipPrivate::YyToolTipPrivate(QObject* parent)
    : QObject{parent}
{
    _pOpacity = 1;
}

YyToolTipPrivate::~YyToolTipPrivate()
{
}

bool YyToolTipPrivate::eventFilter(QObject* watched, QEvent* event)
{
    Q_Q(YyToolTip);
    switch (event->type())
    {
    case QEvent::Enter:
    {
        QTimer::singleShot(_pShowDelayMsec, this, [=]() {
            _doShowAnimation();
        });
        if (_pDisplayMsec > -1)
        {
            QTimer::singleShot(_pDisplayMsec, this, [=]() {
                q->hide();
            });
        }
        break;
    }
    case QEvent::Leave:
    {
        QTimer::singleShot(_pHideDelayMsec, this, [=]() {
            q->hide();
        });
        break;
    }
    case QEvent::HoverMove:
    case QEvent::MouseMove:
    {
        _updatePos();
        break;
    }
    default:
    {
        break;
    }
    }
    return QObject::eventFilter(watched, event);
}

void YyToolTipPrivate::_doShowAnimation()
{
    Q_Q(YyToolTip);
    QPoint cursorPoint = QCursor::pos();
    q->move(cursorPoint.x() + 10, cursorPoint.y());
    q->show();
    // windowOpacity为Qt固有属性
    QPropertyAnimation* showAnimation = new QPropertyAnimation(q, "windowOpacity");
    showAnimation->setEasingCurve(QEasingCurve::InOutSine);
    showAnimation->setDuration(250);
    showAnimation->setStartValue(0);
    showAnimation->setEndValue(1);
    showAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void YyToolTipPrivate::_updatePos()
{
    Q_Q(YyToolTip);
    if (q->isVisible())
    {
        QPoint cursorPoint = QCursor::pos();
        q->move(cursorPoint.x() + 10, cursorPoint.y());
    }
}

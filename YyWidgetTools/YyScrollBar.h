#ifndef YySCROLLBAR_H
#define YySCROLLBAR_H

#include <QAbstractScrollArea>
#include <QScrollBar>

#include "YyProperty.h"

class YyScrollBarPrivate;
class Yy_EXPORT YyScrollBar : public QScrollBar
{
    Q_OBJECT
    Q_Q_CREATE(YyScrollBar)
    Q_PROPERTY_CREATE_Q_H(bool, IsAnimation)
    Q_PROPERTY_CREATE_Q_H(qreal, SpeedLimit)
public:
    explicit YyScrollBar(QWidget* parent = nullptr);
    explicit YyScrollBar(Qt::Orientation orientation, QWidget* parent = nullptr);
    explicit YyScrollBar(QScrollBar* originScrollBar, QAbstractScrollArea* parent = nullptr);
    virtual ~YyScrollBar() override;

Q_SIGNALS:
    Q_SIGNAL void rangeAnimationFinished();

protected:
    virtual bool event(QEvent* event) override;
    virtual bool eventFilter(QObject* watched, QEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void wheelEvent(QWheelEvent* event) override;
    virtual void contextMenuEvent(QContextMenuEvent* event) override;
};

#endif // YySCROLLBAR_H

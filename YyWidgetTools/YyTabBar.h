#ifndef YyTABBAR_H
#define YyTABBAR_H

#include <QDrag>
#include <QTabBar>

#include "YyProperty.h"
class YyTabBarPrivate;
class Yy_EXPORT YyTabBar : public QTabBar
{
    Q_OBJECT
    Q_Q_CREATE(YyTabBar)
    Q_PROPERTY_CREATE_Q_H(QSize, TabSize)
public:
    explicit YyTabBar(QWidget* parent = nullptr);
    ~YyTabBar() override;
Q_SIGNALS:
    Q_SIGNAL void tabDragCreate(QMimeData* mimeData);
    Q_SIGNAL void tabDragEnter(QMimeData* mimeData);
    Q_SIGNAL void tabDragLeave(QMimeData* mimeData);
    Q_SIGNAL void tabDragDrop(QMimeData* mimeData);

protected:
    virtual QSize sizeHint() const override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void dragEnterEvent(QDragEnterEvent* event) override;
    virtual void dragMoveEvent(QDragMoveEvent* event) override;
    virtual void dragLeaveEvent(QDragLeaveEvent* event) override;
    virtual void dropEvent(QDropEvent* event) override;
    virtual void wheelEvent(QWheelEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;
};

#endif // YyTABBAR_H

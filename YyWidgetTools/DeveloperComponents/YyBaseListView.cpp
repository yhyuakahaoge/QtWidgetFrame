#include "YyBaseListView.h"

#include <QMouseEvent>

#include "YyScrollBar.h"
YyBaseListView::YyBaseListView(QWidget* parent)
    : QListView(parent)
{
    setObjectName("YyBaseListView");
    setStyleSheet(
        "YyBaseListView{background-color: transparent;border:0px;}"
        "YyBaseListView::item{border:none;}");
    // 拖拽或者键盘操作时 禁止滚动
    setAutoScroll(false);
    // 禁用焦点 无高亮 无聚焦
    setFocusPolicy(Qt::NoFocus);
    setVerticalScrollBar(new YyScrollBar(this));
    setHorizontalScrollBar(new YyScrollBar(this));
    setSelectionMode(QAbstractItemView::NoSelection);
    setMouseTracking(true);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
}

YyBaseListView::~YyBaseListView()
{
}

void YyBaseListView::wheelEvent(QWheelEvent* event)
{
    QListView::wheelEvent(event);
    event->accept();
}

void YyBaseListView::mousePressEvent(QMouseEvent* event)
{
    Q_EMIT mousePress(indexAt(event->pos()));
    QListView::mousePressEvent(event);
}

void YyBaseListView::mouseReleaseEvent(QMouseEvent* event)
{
    Q_EMIT mouseRelease(indexAt(event->pos()));
    QListView::mouseReleaseEvent(event);
}

void YyBaseListView::mouseDoubleClickEvent(QMouseEvent* event)
{
    Q_EMIT mouseDoubleClick(indexAt(event->pos()));
    QListView::mouseDoubleClickEvent(event);
}

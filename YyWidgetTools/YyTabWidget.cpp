#include "YyTabWidget.h"

#include "YyTabBar.h"
#include "YyTabWidgetPrivate.h"
#include <QDebug>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QPainter>
Q_PROPERTY_CREATE_Q_CPP(YyTabWidget, bool, IsTabTransparent);
Q_PROPERTY_CREATE_Q_CPP(YyTabWidget, bool, IsContainerAcceptDrops);
YyTabWidget::YyTabWidget(QWidget* parent)
    : QTabWidget(parent), d_ptr(new YyTabWidgetPrivate())
{
    Q_D(YyTabWidget);
    d->q_ptr = this;
    d->_pIsContainerAcceptDrops = false;
    d->_pIsTabTransparent = false;
    setObjectName("YyTabWidget");
    setAcceptDrops(true);
    d->_tabBar = new YyTabBar(this);
    setTabBar(d->_tabBar);
    connect(d->_tabBar, &YyTabBar::tabDragCreate, d, &YyTabWidgetPrivate::onTabDragCreate);
    connect(d->_tabBar, &YyTabBar::tabDragEnter, d, &YyTabWidgetPrivate::onTabDragEnter);
    connect(d->_tabBar, &YyTabBar::tabDragLeave, d, &YyTabWidgetPrivate::onTabDragLeave);
    connect(d->_tabBar, &YyTabBar::tabDragDrop, d, &YyTabWidgetPrivate::onTabDragDrop);
    connect(d->_tabBar, &YyTabBar::tabCloseRequested, d, &YyTabWidgetPrivate::onTabCloseRequested);
}

YyTabWidget::~YyTabWidget()
{
    Q_D(YyTabWidget);
    d->_clearAllTabWidgetList();
}

void YyTabWidget::setTabSize(QSize tabSize)
{
    Q_D(YyTabWidget);
    d->_tabBar->setTabSize(tabSize);
}

QSize YyTabWidget::getTabSize() const
{
    Q_D(const YyTabWidget);
    return d->_tabBar->getTabSize();
}

void YyTabWidget::setTabPosition(TabPosition position)
{
    if (position == QTabWidget::North || position == QTabWidget::South)
    {
        QTabWidget::setTabPosition(position);
    }
}

void YyTabWidget::paintEvent(QPaintEvent* event)
{
    Q_D(YyTabWidget);
    if (!d->_pIsTabTransparent)
    {
        QTabWidget::paintEvent(event);
    }
}

void YyTabWidget::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->property("DragType").toString() == "YyTabBarDrag")
    {
        event->acceptProposedAction();
    }
    QTabWidget::dragEnterEvent(event);
}

void YyTabWidget::dropEvent(QDropEvent* event)
{
    Q_D(YyTabWidget);
    if (d->_pIsContainerAcceptDrops && event->mimeData()->property("YyTabWidgetObject").value<YyTabWidget*>() != this)
    {
        QMimeData* data = const_cast<QMimeData*>(event->mimeData());
        data->setProperty("TabDropIndex", count());
        d->onTabDragDrop(data);
        event->accept();
    }
    QTabWidget::dropEvent(event);
}

void YyTabWidget::tabInserted(int index)
{
    Q_D(YyTabWidget);
    QWidget* tabWidget = widget(index);
    if (!tabWidget->property("IsMetaWidget").toBool() && !tabWidget->property("YyOriginTabWidget").isValid())
    {
        d->_allTabWidgetList.append(widget(index));
    }
    QTabWidget::tabInserted(index);
}

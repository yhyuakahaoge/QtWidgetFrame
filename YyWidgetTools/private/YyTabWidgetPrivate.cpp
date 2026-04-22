#include "YyTabWidgetPrivate.h"

#include "YyCustomTabWidget.h"
#include "YyTabBar.h"
#include "YyTabWidget.h"
#include <QApplication>
#include <QDebug>
#include <QMimeData>
#include <QMouseEvent>
#include <QTimer>
#include <QWindow>
YyDragMonitor::YyDragMonitor(QObject* parent)
    : QObject(parent)
{
    _pIsInDrag = false;
}

YyDragMonitor::~YyDragMonitor()
{
}

YyTabWidgetPrivate::YyTabWidgetPrivate(QObject* parent)
    : QObject{parent}
{
}

YyTabWidgetPrivate::~YyTabWidgetPrivate()
{
}

void YyTabWidgetPrivate::onTabDragCreate(QMimeData* mimeData)
{
    Q_Q(YyTabWidget);
    if (YyDragMonitor::getInstance()->getIsInDrag())
    {
        return;
    }
    YyDragMonitor::getInstance()->setIsInDrag(true);
    mimeData->setProperty("YyTabWidgetObject", QVariant::fromValue(q));
    int index = q->currentIndex();
    QString tabText = q->tabText(index);
    QIcon tabIcon = q->tabIcon(index);
    QWidget* dragWidget = q->widget(index);
    dragWidget->setProperty("TabIcon", q->tabIcon(index));
    dragWidget->setProperty("TabText", q->tabText(index));
    QWidget* originTabWidget = dragWidget->property("YyOriginTabWidget").value<YyTabWidget*>();
    if (!originTabWidget && !dragWidget->property("IsMetaWidget").toBool())
    {
        dragWidget->setProperty("YyOriginTabWidget", QVariant::fromValue<YyTabWidget*>(q));
        originTabWidget = q;
    }
    mimeData->setProperty("DragWidget", QVariant::fromValue(dragWidget));
    YyTabBar* tabBarObject = mimeData->property("YyTabBarObject").value<YyTabBar*>();
    QMouseEvent releaseEvent(QEvent::MouseButtonRelease, QPoint(-1, -1), QPoint(-1, -1), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::sendEvent(tabBarObject, &releaseEvent);
    if (!originTabWidget)
    {
        originTabWidget = dragWidget->property("YyFloatParentWidget").value<QWidget*>();
    }
    bool isFloatWidget = mimeData->property("IsFloatWidget").toBool();
    QSize tabSize = mimeData->property("TabSize").toSize();
    YyCustomTabWidget* floatWidget = nullptr;
    if (isFloatWidget)
    {
        floatWidget = dynamic_cast<YyCustomTabWidget*>(q->window());
        if (floatWidget->windowHandle())
        {
            floatWidget->windowHandle()->setFlag(Qt::WindowTransparentForInput, true);
        }
    }
    else
    {
        floatWidget = new YyCustomTabWidget(originTabWidget);
        q->removeTab(index);
        // 创建新窗口
        YyTabBar* originCustomTabBar = tabBarObject;
        if (originCustomTabBar && originCustomTabBar->objectName() == "YyCustomTabBar")
        {
            originCustomTabBar->removeTab(index);
        }
        YyTabBar* customTabBar = floatWidget->getCustomTabBar();
        customTabBar->setTabSize(tabSize);
        dragWidget->setProperty("CurrentCustomBar", QVariant::fromValue<YyTabBar*>(customTabBar));
        floatWidget->addTab(dragWidget, tabIcon, tabText);
    }
    QPoint dragPos = mimeData->property("DragPos").toPoint();
    QTimer* dragTimer = new QTimer(this);
    dragTimer->start(10);
    connect(dragTimer, &QTimer::timeout, floatWidget, [=]() {
        if (floatWidget->getIsFinished() && !isFloatWidget)
        {
            dragTimer->stop();
        }
        else
        {
            QPoint cursorPoint = QCursor::pos();
            if (isFloatWidget)
            {
                floatWidget->move(cursorPoint.x() - dragPos.x() - 10, cursorPoint.y() - dragPos.y() - 10);
            }
            else
            {
                floatWidget->move(cursorPoint.x() - tabSize.width() / 2 - 10, cursorPoint.y() - tabSize.height() / 2 - 10);
            }
        }
    });
    QDrag* drag = new QDrag(this);
    QPixmap pix(1, 1);
    pix.fill(Qt::transparent);
    drag->setPixmap(pix);
    drag->setMimeData(mimeData);
    connect(drag, &QDrag::destroyed, this, [=]() {
        dragTimer->deleteLater();
    });
    drag->setHotSpot(QPoint(tabSize.width() / 2, 0));
    QTimer::singleShot(1, this, [=]() {
        floatWidget->show();
        if (floatWidget->windowHandle())
        {
            floatWidget->windowHandle()->setFlag(Qt::WindowTransparentForInput, true);
        }
        if (!isFloatWidget)
        {
            floatWidget->resize(700, 500);
        }
    });
    auto ret = drag->exec();
    YyDragMonitor::getInstance()->setIsInDrag(false);
    YyCustomTabWidget* tempFloatWidget = mimeData->property("TempFloatWidget").value<YyCustomTabWidget*>();
    if (tempFloatWidget)
    {
        if (ret == Qt::IgnoreAction)
        {
            if (tempFloatWidget->windowHandle())
            {
                tempFloatWidget->windowHandle()->setFlag(Qt::WindowTransparentForInput, false);
            }
        }
        else
        {
            tempFloatWidget->deleteLater();
        }
        floatWidget->deleteLater();
    }
    else
    {
        if (floatWidget->windowHandle())
        {
            floatWidget->windowHandle()->setFlag(Qt::WindowTransparentForInput, false);
        }
    }
}

void YyTabWidgetPrivate::onTabDragEnter(QMimeData* mimeData)
{
    Q_Q(YyTabWidget);
    mimeData->setProperty("YyTabBarObject", QVariant::fromValue<YyTabBar*>(dynamic_cast<YyTabBar*>(q->tabBar())));
    onTabDragDrop(mimeData);
}

void YyTabWidgetPrivate::onTabDragLeave(QMimeData* mimeData)
{
    Q_Q(YyTabWidget);
    QWidget* dragWidget = mimeData->property("DragWidget").value<QWidget*>();
    int index = q->indexOf(dragWidget);
    mimeData->setProperty("YyTabWidgetObject", QVariant::fromValue(q));
    QString tabText = q->tabText(index);
    QIcon tabIcon = q->tabIcon(index);

    YyTabBar* tabBarObject = mimeData->property("YyTabBarObject").value<YyTabBar*>();
    mimeData->setProperty("DragWidget", QVariant::fromValue(dragWidget));
    q->removeTab(index);
    // 创建新窗口
    if (_customTabBar && _customTabBar != tabBarObject)
    {
        _customTabBar->removeTab(index);
    }
    QWidget* originTabWidget = dragWidget->property("YyOriginTabWidget").value<YyTabWidget*>();
    if (!originTabWidget)
    {
        originTabWidget = dragWidget->property("YyFloatParentWidget").value<QWidget*>();
    }
    YyCustomTabWidget* floatWidget = new YyCustomTabWidget(originTabWidget);
    QSize tabSize = mimeData->property("TabSize").toSize();
    YyTabBar* customTabBar = floatWidget->getCustomTabBar();
    customTabBar->setTabSize(tabSize);
    dragWidget->setProperty("CurrentCustomBar", QVariant::fromValue<YyTabBar*>(customTabBar));
    floatWidget->addTab(dragWidget, tabIcon, tabText);
    floatWidget->show();
    floatWidget->resize(700, 500);
    if (floatWidget->windowHandle())
    {
        floatWidget->windowHandle()->setFlag(Qt::WindowTransparentForInput, true);
    }
    QPoint cursorPoint = QCursor::pos();
    floatWidget->move(cursorPoint.x() - tabSize.width() / 2, cursorPoint.y() - tabSize.height() / 2);
    QTimer* dragTimer = new QTimer(this);
    dragTimer->start(10);
    connect(dragTimer, &QTimer::timeout, floatWidget, [=]() {
        QPoint cursorPoint = QCursor::pos();
        floatWidget->move(cursorPoint.x() - tabSize.width() / 2 - 10, cursorPoint.y() - tabSize.height() / 2 - 10);
    });
    connect(mimeData, &QMimeData::destroyed, this, [=]() {
        dragTimer->deleteLater();
    });
    YyCustomTabWidget* tempFloatWidget = mimeData->property("TempFloatWidget").value<YyCustomTabWidget*>();
    if (tempFloatWidget)
    {
        tempFloatWidget->deleteLater();
    }
    mimeData->setProperty("TempFloatWidget", QVariant::fromValue<YyCustomTabWidget*>(floatWidget));
}

void YyTabWidgetPrivate::onTabDragDrop(QMimeData* mimeData)
{
    Q_Q(YyTabWidget);
    QWidget* dragWidget = mimeData->property("DragWidget").value<QWidget*>();
    QString tabText = dragWidget->property("TabText").toString();
    QIcon tabIcon = dragWidget->property("TabIcon").value<QIcon>();
    int dropIndex = mimeData->property("TabDropIndex").toInt();
    if (dropIndex < 0)
    {
        dropIndex = q->count();
    }
    q->insertTab(dropIndex, dragWidget, tabIcon, tabText);
    q->setCurrentWidget(dragWidget);
    if (_customTabBar)
    {
        dragWidget->setProperty("CurrentCustomBar", QVariant::fromValue<YyTabBar*>(_customTabBar));
        _customTabBar->insertTab(dropIndex, tabIcon, tabText);
        _customTabBar->setCurrentIndex(dropIndex);
    }
}

void YyTabWidgetPrivate::onTabCloseRequested(int index)
{
    Q_Q(YyTabWidget);
    QWidget* closeWidget = q->widget(index);
    YyTabWidget* originTabWidget = closeWidget->property("YyOriginTabWidget").value<YyTabWidget*>();
    if (originTabWidget && originTabWidget != q)
    {
        YyTabBar* customTabBar = closeWidget->property("CurrentCustomBar").value<YyTabBar*>();
        if (customTabBar)
        {
            customTabBar->removeTab(index);
            closeWidget->setProperty("CurrentCustomBar", QVariant::fromValue<YyTabBar*>(nullptr));
        }
        originTabWidget->addTab(closeWidget, q->tabIcon(index), q->tabText(index));
        originTabWidget->setCurrentWidget(closeWidget);
    }
    else
    {
        if (!originTabWidget && q->objectName() == "YyCustomTabWidget")
        {
            _customTabBar->removeTab(index);
        }
        q->removeTab(index);
        if (_allTabWidgetList.contains(closeWidget))
        {
            _allTabWidgetList.removeOne(closeWidget);
        }
        closeWidget->deleteLater();
    }
}

void YyTabWidgetPrivate::_clearAllTabWidgetList()
{
    Q_Q(YyTabWidget);
    for (auto widget: _allTabWidgetList)
    {
        auto originTabWidgetVariant = widget->property("YyOriginTabWidget");
        if (originTabWidgetVariant.isValid() && originTabWidgetVariant.value<YyTabWidget*>() == q)
        {
            widget->setProperty("YyOriginTabWidget", QVariant());
        }
    }
    _allTabWidgetList.clear();
}

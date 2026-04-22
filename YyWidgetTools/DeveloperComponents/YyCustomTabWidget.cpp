#include "YyCustomTabWidget.h"

#include "YyAppBar.h"
#include "YyTabBar.h"
#include "YyTabWidget.h"
#include "YyTabWidgetPrivate.h"
#include <QDebug>
#include <QEvent>
#include <QMimeData>
#include <QMouseEvent>
#include <QTimer>
#include <QVBoxLayout>
#include <QVariant>
YyCustomTabWidget::YyCustomTabWidget(QWidget* parent)
    : YyCustomWidget(parent)
{
    _pIsFinished = false;
    resize(700, 500);
    setWindowTitle("");
#ifndef Q_OS_WIN
    setAttribute(Qt::WA_Hover);
#endif
    setMouseTracking(true);
    setWindowIcon(QIcon());
    _customTabWidget = new YyTabWidget(this);
    _customTabWidget->setIsTabTransparent(true);
    _customTabWidget->setObjectName("YyCustomTabWidget");
    QTabBar* originTabBar = _customTabWidget->tabBar();
    originTabBar->hide();
    setAcceptDrops(true);
    _customTabBar = new YyTabBar(this);
    _customTabBar->setObjectName("YyCustomTabBar");
    connect(_customTabBar, &YyTabBar::tabMoved, this, [=](int from, int to) {
        _customTabWidget->tabBar()->moveTab(from, to);
    });
    connect(_customTabBar, &YyTabBar::currentChanged, this, [=](int index) {
        _customTabWidget->setCurrentIndex(index);
    });
    connect(_customTabWidget, &YyTabWidget::currentChanged, this, [=](int index) {
        if (index == -1)
        {
            _pIsFinished = true;
            hide();
        }
    });
    connect(_customTabBar, &YyTabBar::tabCloseRequested, originTabBar, &QTabBar::tabCloseRequested);

    _customTabWidget->d_ptr->_customTabBar = _customTabBar;
    connect(_customTabBar, &YyTabBar::tabDragCreate, _customTabWidget->d_func(), &YyTabWidgetPrivate::onTabDragCreate);
    connect(_customTabBar, &YyTabBar::tabDragDrop, _customTabWidget->d_func(), &YyTabWidgetPrivate::onTabDragDrop);
    connect(_customTabBar, &YyTabBar::tabDragEnter, _customTabWidget->d_func(), &YyTabWidgetPrivate::onTabDragEnter);
    connect(_customTabBar, &YyTabBar::tabDragLeave, _customTabWidget->d_func(), &YyTabWidgetPrivate::onTabDragLeave);
    // 在自定义appbar中最左侧添加TabBar
    QWidget* customWidget = new QWidget(this);
    QVBoxLayout* customLayout = new QVBoxLayout(customWidget);
    customLayout->setContentsMargins(10, 0, 10, 0);
    customLayout->addStretch();
    customLayout->addWidget(_customTabBar);
    _appBar->setCustomWidget(YyAppBarType::LeftArea, customWidget, this, "processHitTest");
    setCentralWidget(_customTabWidget);
}

YyCustomTabWidget::~YyCustomTabWidget()
{
    while (_customTabWidget->count() > 0)
    {
        QWidget* closeWidget = _customTabWidget->widget(0);
        YyTabWidget* originTabWidget = closeWidget->property("YyOriginTabWidget").value<YyTabWidget*>();
        if (originTabWidget)
        {
            closeWidget->setProperty("CurrentCustomBar", QVariant::fromValue<YyTabBar*>(nullptr));
            originTabWidget->addTab(closeWidget, _customTabWidget->tabIcon(0), _customTabWidget->tabText(0));
            originTabWidget->setCurrentWidget(closeWidget);
        }
        else
        {
            _customTabWidget->removeTab(0);
        }
    }
}

void YyCustomTabWidget::addTab(QWidget* widget, QIcon tabIcon, const QString& tabTitle)
{
    _customTabBar->addTab(tabIcon, tabTitle);
    _customTabWidget->addTab(widget, tabIcon, tabTitle);
}

YyTabBar* YyCustomTabWidget::getCustomTabBar() const
{
    return _customTabBar;
}

YyTabWidget* YyCustomTabWidget::getCustomTabWidget() const
{
    return _customTabWidget;
}

bool YyCustomTabWidget::processHitTest()
{
    auto point = _customTabBar->mapFromGlobal(QCursor::pos());
    return _customTabBar->tabAt(point) < 0;
}

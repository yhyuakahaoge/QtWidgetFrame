#include "YyNavigationView.h"

#include <QDebug>
#include <QHeaderView>
#include <QModelIndex>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollBar>
#include <QScroller>

#include "YyMenu.h"
#include "YyNavigationModel.h"
#include "YyNavigationNode.h"
#include "YyNavigationStyle.h"
#include "YyScrollBar.h"
#include "YyToolTip.h"
YyNavigationView::YyNavigationView(QWidget* parent)
    : QTreeView(parent)
{
    setObjectName("YyNavigationView");
    setStyleSheet("#YyNavigationView{background-color:transparent;}");
    setAnimated(true);
    // 隐藏表头
    setHeaderHidden(true);
    // 隐藏展开装饰
    setRootIsDecorated(false);
    setExpandsOnDoubleClick(false);
    setAutoScroll(false);
    setMouseTracking(true);
    // 不用系统默认选中高光
    setSelectionMode(QAbstractItemView::NoSelection);

    // 滚动条设置
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    YyScrollBar* vScrollBar = new YyScrollBar(this);
    connect(vScrollBar, &YyScrollBar::rangeAnimationFinished, this, [=]() {
        doItemsLayout();
    });
    setVerticalScrollBar(vScrollBar);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // 按像素滚动
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    YyScrollBar* floatVScrollBar = new YyScrollBar(vScrollBar, this);
    floatVScrollBar->setIsAnimation(true);
    floatVScrollBar->installEventFilter(this);

    _navigationStyle = new YyNavigationStyle(this->style());
    _navigationStyle->setNavigationView(this);
    setStyle(_navigationStyle);

    // 鼠标左键拖拽
    QScroller::grabGesture(this->viewport(), QScroller::LeftMouseButtonGesture);
    // 获取视口QScroller对象
    QScroller* scroller = QScroller::scroller(this->viewport());
    // 获取默认配置
    QScrollerProperties properties = scroller->scrollerProperties();
    // 关闭延迟 鼠标按下立即响应
    properties.setScrollMetric(QScrollerProperties::MousePressEventDelay, 0);
    // 关闭水平方向回弹
    properties.setScrollMetric(QScrollerProperties::HorizontalOvershootPolicy, QScrollerProperties::OvershootAlwaysOff);
    // 同上
    properties.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy, QScrollerProperties::OvershootAlwaysOn);
    // 拖拽系数
    properties.setScrollMetric(QScrollerProperties::OvershootDragResistanceFactor, 0.35);
    // 回弹动画
    properties.setScrollMetric(QScrollerProperties::OvershootScrollTime, 0.5);
    // 滑动帧率
    properties.setScrollMetric(QScrollerProperties::FrameRate, QScrollerProperties::Fps60);
    scroller->setScrollerProperties(properties);

    connect(scroller, &QScroller::stateChanged, this, [=](QScroller::State newstate) {
        if (newstate == QScroller::Pressed)
        {
            _navigationStyle->setPressIndex(indexAt(mapFromGlobal(QCursor::pos())));
            viewport()->update();
        }
        else if (newstate == QScroller::Scrolling || newstate == QScroller::Inactive)
        {
            _navigationStyle->setPressIndex(QModelIndex());
        }
    });

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &YyNavigationView::customContextMenuRequested, this, &YyNavigationView::onCustomContextMenuRequested);
}

YyNavigationView::~YyNavigationView()
{
}

void YyNavigationView::navigationNodeStateChange(QVariantMap data)
{
    this->_navigationStyle->navigationNodeStateChange(data);
}

void YyNavigationView::onCustomContextMenuRequested(const QPoint& pos)
{
    if (!_pNavigationBarPrivate->_pIsAllowPageOpenInNewWindow)
    {
        return;
    }
    QModelIndex posIndex = indexAt(pos);
    if (!posIndex.isValid())
    {
        return;
    }
    YyNavigationNode* posNode = static_cast<YyNavigationNode*>(posIndex.internalPointer());
    if (!posNode->getIsExpanderNode() && !posNode->getIsCategoryNode())
    {
        YyMenu menu;
        menu.setMenuItemHeight(27);
        QAction* openAction = menu.addYyIconAction(YyIconType::ObjectGroup, "在新窗口中打开");
        connect(openAction, &QAction::triggered, this, [=]() {
            Q_EMIT navigationOpenNewWindow(posNode->getNodeKey());
        });
        menu.exec(mapToGlobal(pos));
    }
}

void YyNavigationView::mouseMoveEvent(QMouseEvent* event)
{
    _doCompactToolTip();
    QTreeView::mouseMoveEvent(event);
}

void YyNavigationView::mouseDoubleClickEvent(QMouseEvent* event)
{
    _navigationStyle->setPressIndex(indexAt(event->pos()));
    viewport()->update();
    QTreeView::mouseDoubleClickEvent(event);
}

void YyNavigationView::mouseReleaseEvent(QMouseEvent* event)
{
    QTreeView::mouseReleaseEvent(event);
    if (event->button() == Qt::LeftButton)
    {
        QModelIndex index = indexAt(event->pos());
        if (index.isValid())
        {
            Q_EMIT navigationClicked(index);
        }
        _navigationStyle->setPressIndex(QModelIndex());
    }
}

bool YyNavigationView::eventFilter(QObject* watched, QEvent* event)
{
    switch (event->type())
    {
    case QEvent::MouseMove:
    case QEvent::HoverMove:
    {
        _doCompactToolTip();
        break;
    }
    default:
    {
        break;
    }
    }
    return QAbstractItemView::eventFilter(watched, event);
}

// compact模式下导航栏只显示图标 ToolTip辅助显示导航标题
void YyNavigationView::_doCompactToolTip()
{
    if (_pNavigationBarPrivate->_currentDisplayMode == YyNavigationType::NavigationDisplayMode::Compact)
    {
        if (!_compactToolTip)
        {
            _compactToolTip = new YyToolTip(this);
        }
        QModelIndex posIndex = indexAt(mapFromGlobal(QCursor::pos()));
        if (!posIndex.isValid())
        {
            _compactToolTip->hide();
            return;
        }
        YyNavigationNode* posNode = static_cast<YyNavigationNode*>(posIndex.internalPointer());
        _compactToolTip->setToolTip(posNode->getNodeTitle());
        _compactToolTip->updatePos();
        _compactToolTip->show();
    }
    else
    {
        if (_compactToolTip)
        {
            _compactToolTip->deleteLater();
            _compactToolTip = nullptr;
        }
    }
}

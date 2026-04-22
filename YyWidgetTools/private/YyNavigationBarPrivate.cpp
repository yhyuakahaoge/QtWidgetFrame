#include "YyNavigationBarPrivate.h"
#include "YyApplication.h"
#include "YyBaseListView.h"
#include "YyCustomTabWidget.h"
#include "YyCustomWidget.h"
#include "YyFooterDelegate.h"
#include "YyFooterModel.h"
#include "YyIconButton.h"
#include "YyInteractiveCard.h"
#include "YyMenu.h"
#include "YyNavigationBar.h"
#include "YyNavigationModel.h"
#include "YyNavigationNode.h"
// #include "YyNavigationRouter.h"
#include "YyNavigationView.h"
#include "YyToolButton.h"
#include <QApplication>
#include <QDebug>
#include <QEvent>
#include <QLayout>
#include <QPropertyAnimation>
#include <QScrollBar>
#include <QTimer>
YyNavigationBarPrivate::YyNavigationBarPrivate(QObject* parent)
    : QObject{parent}
{
}

YyNavigationBarPrivate::~YyNavigationBarPrivate()
{
}

void YyNavigationBarPrivate::onNavigationOpenNewWindow(QString nodeKey)
{
    Q_Q(YyNavigationBar);
    const QMetaObject* meta = _pageMetaMap.value(nodeKey);
    if (!meta)
    {
        return;
    }
    QWidget* widget = dynamic_cast<QWidget*>(meta->newInstance());
    if (widget)
    {
        widget->setProperty("YyPageKey", nodeKey);
        widget->setProperty("IsMetaWidget", true);
        widget->setProperty("YyFloatParentWidget", QVariant::fromValue(q));
        widget->installEventFilter(this);
        YyCustomTabWidget* floatWidget = new YyCustomTabWidget(q);
        floatWidget->addTab(widget, widget->windowIcon(), widget->windowTitle());
        floatWidget->show();
        Q_EMIT q->pageOpenInNewWindow(nodeKey);
    }
}

// void YyNavigationBarPrivate::onNavigationRoute(QVariantMap routeData)
// {
//     // Q_Q(YyNavigationBar);
//     // bool isRouteBack = routeData.value("YyRouteBackMode").toBool();
//     // QString pageKey = isRouteBack ? routeData.value("YyBackPageKey").toString() : routeData.value("YyForwardPageKey").toString();
//     // q->navigation(pageKey, false, isRouteBack);
// }

// NavigationModel在addNode时默认将第一个node设置为selectedNode
void YyNavigationBarPrivate::onTreeViewClicked(const QModelIndex& index, bool isLogRoute, bool isRouteBack)
{
    Q_Q(YyNavigationBar);
    if (index.isValid())
    {
        YyNavigationNode* node = static_cast<YyNavigationNode*>(index.internalPointer());
        if (!node)
        {
            return;
        }
        if (node->getIsCategoryNode())
        {
            Q_EMIT q->navigationNodeClicked(YyNavigationType::CategoryNode, node->getNodeKey(), isRouteBack);
            return;
        }
        if (node->getIsExpanderNode())
        {
            _expandOrCollapseExpanderNode(node, !_navigationView->isExpanded(index));
        }
        else
        {
            if (node->getKeyPoints())
            {
                node->setKeyPoints(0);
                _navigationView->update();
            }
            YyNavigationNode* selectedNode = _navigationModel->getSelectedNode();
            if (selectedNode != node)
            {
                // 记录跳转
                // if (isLogRoute)
                // {
                //     QVariantMap routeData = QVariantMap();
                //     QString backPageKey;
                //     if (selectedNode)
                //     {
                //         backPageKey = selectedNode->getNodeKey();
                //     }
                //     else
                //     {
                //         if (_footerModel->getSelectedNode())
                //         {
                //             backPageKey = _footerModel->getSelectedNode()->getNodeKey();
                //         }
                //     }
                //     routeData.insert("YyBackPageKey", backPageKey);
                //     routeData.insert("YyForwardPageKey", node->getNodeKey());
                //     YyNavigationRouter::getInstance()->navigationRoute(this, "onNavigationRoute", routeData);
                // }
                // Q_EMIT q->navigationNodeClicked(YyNavigationType::PageNode, node->getNodeKey(), isRouteBack);

                if (_footerModel->getSelectedNode())
                {
                    _footerView->clearSelection();
                    QVariantMap footerPostData = QVariantMap();
                    footerPostData.insert("SelectMarkChanged", true);
                    footerPostData.insert("LastSelectedNode", QVariant::fromValue(_footerModel->getSelectedNode()));
                    footerPostData.insert("SelectedNode", QVariant::fromValue(nullptr));
                    _footerModel->setSelectedNode(nullptr);
                    _footerDelegate->navigationNodeStateChange(footerPostData);
                }
                QVariantMap postData = QVariantMap();
                postData.insert("SelectMarkChanged", true);
                if (_navigationModel->getSelectedExpandedNode())
                {
                    postData.insert("LastSelectedNode", QVariant::fromValue(_navigationModel->getSelectedExpandedNode()));
                }
                else
                {
                    postData.insert("LastSelectedNode", QVariant::fromValue(_navigationModel->getSelectedNode()));
                }
                if (_currentDisplayMode == YyNavigationType::Compact)
                {
                    YyNavigationNode* originNode = node->getOriginalNode();
                    if (originNode == node)
                    {
                        postData.insert("SelectedNode", QVariant::fromValue(node));
                    }
                    else
                    {
                        if (originNode == _navigationModel->getSelectedExpandedNode())
                        {
                            _navigationModel->setSelectedNode(node);
                            _resetNodeSelected();
                            return;
                        }
                        _navigationModel->setSelectedExpandedNode(originNode);
                        postData.insert("SelectedNode", QVariant::fromValue(originNode));
                    }
                }
                else
                {
                    postData.insert("SelectedNode", QVariant::fromValue(node));
                }
                _navigationModel->setSelectedNode(node);
                _navigationView->navigationNodeStateChange(postData);
                if (!node->getIsVisible() && _currentDisplayMode != YyNavigationType::Compact)
                {
                    _expandSelectedNodeParent();
                }
            }
        }
        _resetNodeSelected();
    }
}

void YyNavigationBarPrivate::onFooterViewClicked(const QModelIndex& index, bool isLogRoute, bool isRouteBack)
{
    Q_Q(YyNavigationBar);
    YyNavigationNode* node = index.data(Qt::UserRole).value<YyNavigationNode*>();
    if (node->getKeyPoints())
    {
        node->setKeyPoints(0);
        _navigationView->update();
    }
    YyNavigationNode* selectedNode = _footerModel->getSelectedNode();

    if (selectedNode != node)
    {
        // 记录跳转
        // if (isLogRoute && node->getIsHasFooterPage())
        // {
        //     QVariantMap routeData = QVariantMap();
        //     QString backPageKey;
        //     if (selectedNode)
        //     {
        //         backPageKey = selectedNode->getNodeKey();
        //     }
        //     else
        //     {
        //         if (_navigationModel->getSelectedNode())
        //         {
        //             backPageKey = _navigationModel->getSelectedNode()->getNodeKey();
        //         }
        //     }
        //     routeData.insert("YyBackPageKey", backPageKey);
        //     routeData.insert("YyForwardPageKey", node->getNodeKey());
        //     YyNavigationRouter::getInstance()->navigationRoute(this, "onNavigationRoute", routeData);
        // }
        // Q_EMIT q->navigationNodeClicked(YyNavigationType::FooterNode, node->getNodeKey(), isRouteBack);

        if (node->getIsHasFooterPage())
        {
            if (_navigationModel->getSelectedNode() || _navigationModel->getSelectedExpandedNode())
            {
                QVariantMap mainPostData = QVariantMap();
                mainPostData.insert("SelectMarkChanged", true);
                mainPostData.insert("LastSelectedNode", QVariant::fromValue(_navigationModel->getSelectedExpandedNode() ? _navigationModel->getSelectedExpandedNode() : _navigationModel->getSelectedNode()));
                mainPostData.insert("SelectedNode", QVariant::fromValue(nullptr));
                _navigationView->clearSelection();
                _navigationView->navigationNodeStateChange(mainPostData);
                _navigationModel->setSelectedExpandedNode(nullptr);
                _navigationModel->setSelectedNode(nullptr);
            }
            _footerView->clearSelection();
            _footerView->selectionModel()->select(index, QItemSelectionModel::Select);
            QVariantMap postData = QVariantMap();
            postData.insert("SelectMarkChanged", true);
            postData.insert("LastSelectedNode", QVariant::fromValue(_footerModel->getSelectedNode()));
            postData.insert("SelectedNode", QVariant::fromValue(node));
            _footerDelegate->navigationNodeStateChange(postData);
            _footerModel->setSelectedNode(node);
        }
    }
}

bool YyNavigationBarPrivate::eventFilter(QObject* watched, QEvent* event)
{
    switch (event->type())
    {
    case QEvent::Show:
    {
        QString nodeKey = watched->property("YyPageKey").toString();
        if (!nodeKey.isNull())
        {
            _pageNewWindowCountMap[nodeKey] += 1;
        }
        break;
    }
    case QEvent::HideToParent:
    {
        QString nodeKey = watched->property("YyPageKey").toString();
        if (!nodeKey.isNull())
        {
           _pageNewWindowCountMap[nodeKey] -= 1;
        }
        break;
    }
    default:
    {
        break;
    }
    }
    return QObject::eventFilter(watched, event);
}

void YyNavigationBarPrivate::_initNodeModelIndex(const QModelIndex& parentIndex)
{
    int rowCount = _navigationModel->rowCount(parentIndex);
    for (int row = 0; row < rowCount; ++row)
    {
        QModelIndex index = _navigationModel->index(row, 0, parentIndex);
        // YyNavigationNode* childNode = static_cast<YyNavigationNode*>(index.internalPointer());
        // childNode->setModelIndex(index);
        if (_navigationModel->hasChildren(index))
        {
            _initNodeModelIndex(index);
        }
    }
}

void YyNavigationBarPrivate::_resetNodeSelected()
{
    _navigationView->clearSelection();
    YyNavigationNode* selectedNode = _navigationModel->getSelectedNode();
    if (!selectedNode || !selectedNode->getModelIndex().isValid())
    {
        return;
    }
    if (selectedNode->getParentNode()->getIsRootNode() || selectedNode->getIsVisible())
    {
        // 设置item为选中状态
        _navigationView->selectionModel()->select(selectedNode->getModelIndex(), QItemSelectionModel::Select);
        // if (_navigationModel->getSelectedExpandedNode())
        // {
        //     QVariantMap postData = QVariantMap();
        //     postData.insert("SelectMarkChanged", true);
        //     postData.insert("LastSelectedNode", QVariant::fromValue(_navigationModel->getSelectedExpandedNode()));
        //     postData.insert("SelectedNode", QVariant::fromValue(selectedNode));
        //     _navigationView->navigationNodeStateChange(postData);
        // }
        _navigationModel->setSelectedExpandedNode(nullptr);
    }
    else
    {
        YyNavigationNode* parentNode = selectedNode->getParentNode();
        while (parentNode && !parentNode->getParentNode()->getIsRootNode() && !parentNode->getIsVisible())
        {
            parentNode = parentNode->getParentNode();
        }
        if (!parentNode)
        {
            return;
        }
        // 单级节点展开/收起时Mark变化
        if (!_navigationModel->getSelectedExpandedNode())
        {
            QVariantMap postData = QVariantMap();
            postData.insert("SelectMarkChanged", true);
            postData.insert("LastSelectedNode", QVariant::fromValue(_navigationModel->getSelectedNode()));
            postData.insert("SelectedNode", QVariant::fromValue(parentNode));
            _navigationView->navigationNodeStateChange(postData);
        }
        else
        {
            // 多级节点
            if (_navigationModel->getSelectedExpandedNode() != parentNode)
            {
                // 同一起源节点展开/收起时的Mark变化
                if (_navigationModel->getSelectedExpandedNode()->getOriginalNode() == parentNode->getOriginalNode())
                {
                    QVariantMap postData = QVariantMap();
                    postData.insert("SelectMarkChanged", true);
                    postData.insert("LastSelectedNode", QVariant::fromValue(_navigationModel->getSelectedExpandedNode()));
                    postData.insert("SelectedNode", QVariant::fromValue(parentNode));
                    _navigationView->navigationNodeStateChange(postData);
                }
            }
        }
        _navigationModel->setSelectedExpandedNode(parentNode);
        _navigationView->selectionModel()->select(parentNode->getModelIndex(), QItemSelectionModel::Select);
    }
}

void YyNavigationBarPrivate::_expandSelectedNodeParent()
{
    YyNavigationNode* parentNode = _navigationModel->getSelectedNode()->getParentNode();
    while (parentNode && !parentNode->getIsRootNode())
    {
        QVariantMap data;
        data.insert("Expand", QVariant::fromValue(parentNode));
        _navigationView->navigationNodeStateChange(data);
        parentNode->setIsExpanded(true);
        _navigationView->expand(parentNode->getModelIndex());
        parentNode = parentNode->getParentNode();
    }
}

void YyNavigationBarPrivate::_expandOrCollapseExpanderNode(YyNavigationNode* node, bool isExpand)
{
    if (_currentDisplayMode == YyNavigationType::Compact)
    {
        // 为Expand节点弹出菜单
        if (node->getIsHasPageChild())
        {
            //展开菜单
            YyMenu* menu = _compactMenuMap.value(node);
            if (menu)
            {
                QPoint nodeTopRight = _navigationView->mapToGlobal(_navigationView->visualRect(node->getModelIndex()).topRight());
                menu->popup(QPoint(nodeTopRight.x() + 10, nodeTopRight.y()));
            }
        }
    }
    else
    {
        QModelIndex index = node->getModelIndex();
        bool isExpanded = _navigationView->isExpanded(index);
        if (node->getIsHasChild() && isExpand != isExpanded)
        {
            QVariantMap data;
            if (isExpanded)
            {
                // 收起
                data.insert("Collapse", QVariant::fromValue(node));
                node->setIsExpanded(isExpand);
                _navigationView->navigationNodeStateChange(data);
                _navigationView->collapse(index);
            }
            else
            {
                // 展开
                data.insert("Expand", QVariant::fromValue(node));
                node->setIsExpanded(true);
                _navigationView->navigationNodeStateChange(data);
                _navigationView->expand(index);
            }
        }
    }
}

void YyNavigationBarPrivate::_addStackedPage(QWidget* page, QString pageKey)
{
    Q_Q(YyNavigationBar);
    page->setProperty("YyPageKey", pageKey);
    Q_EMIT q->navigationNodeAdded(YyNavigationType::PageNode, pageKey, page);
    YyNavigationNode* node = _navigationModel->getNavigationNode(pageKey);
    QVariantMap suggestData;
    suggestData.insert("YyPageKey", pageKey);
    _suggestDataList.append(YySuggestBox::SuggestData(node->getAwesome(), node->getNodeTitle(), suggestData));
}

void YyNavigationBarPrivate::_addFooterPage(QWidget* page, QString footKey)
{
    Q_Q(YyNavigationBar);
    Q_EMIT q->navigationNodeAdded(YyNavigationType::FooterNode, footKey, page);
    if (page)
    {
        page->setProperty("YyPageKey", footKey);
    }
    _footerView->setFixedHeight(40 * _footerModel->getFooterNodeCount());
    YyNavigationNode* node = _footerModel->getNavigationNode(footKey);
    QVariantMap suggestData;
    suggestData.insert("YyPageKey", footKey);
    _suggestDataList.append(YySuggestBox::SuggestData(node->getAwesome(), node->getNodeTitle(), suggestData));
}

void YyNavigationBarPrivate::_raiseNavigationBar()
{
    Q_Q(YyNavigationBar);
    q->raise();
}

// void YyNavigationBarPrivate::_smoothScrollNavigationView(const QModelIndex& index)
// {
// //     QTimer::singleShot(200, this, [=]() {
// //         if (_currentDisplayMode == YyNavigationType::Compact)
// //         {
// //             return;
// //         }
// //         auto vScrollBar = _navigationView->verticalScrollBar();
// //         int startValue = vScrollBar->value();
// //         _navigationView->scrollTo(index, QAbstractItemView::PositionAtCenter);
// //         int endValue = vScrollBar->value();
// //         QPropertyAnimation* scrollAnimation = new QPropertyAnimation(vScrollBar, "value");
// //         scrollAnimation->setEasingCurve(QEasingCurve::OutSine);
// //         scrollAnimation->setDuration(255);
// //         scrollAnimation->setStartValue(startValue);
// //         scrollAnimation->setEndValue(endValue);
// //         scrollAnimation->start(QAbstractAnimation::DeleteWhenStopped);
// //     });
// // }

// // void YyNavigationBarPrivate::_doComponentAnimation(YyNavigationType::NavigationDisplayMode displayMode, bool isAnimation)
// // {
// //     switch (displayMode)
// //     {
// //     case YyNavigationType::Minimal:
// //     {
// //         _doNavigationBarWidthAnimation(displayMode, isAnimation);
// //         if (_currentDisplayMode == YyNavigationType::Maximal)
// //         {
// //             _userCard->setVisible(false);
// //             _doUserButtonAnimation(true, isAnimation);
// //             _handleNavigationExpandState(true);
// //         }
// //         _currentDisplayMode = displayMode;
// //         break;
// //     }
// //     case YyNavigationType::Compact:
// //     {
// //         _doNavigationBarWidthAnimation(displayMode, isAnimation);
// //         _doNavigationViewWidthAnimation(isAnimation);
// //         if (_currentDisplayMode != YyNavigationType::Minimal)
// //         {
// //             _doUserButtonAnimation(true, isAnimation);
// //             _handleNavigationExpandState(true);
// //         }
// //         _currentDisplayMode = displayMode;
// //         break;
// //     }
// //     case YyNavigationType::Maximal:
// //     {
// //         _doNavigationBarWidthAnimation(displayMode, isAnimation);
// //         _doUserButtonAnimation(false, isAnimation);
// //         _currentDisplayMode = displayMode;
// //         _handleNavigationExpandState(false);
// //         break;
// //     }
// //     default:
// //     {
// //         break;
// //     }
// //     }
// }

// void YyNavigationBarPrivate::_handleNavigationExpandState(bool isSave)
// {
//     // if (isSave)
//     // {
//     //     // 保存展开状态 收起根节点所有子树
//     //     _lastExpandedNodesList = _navigationModel->getRootExpandedNodes();
//     //     for (auto node: _lastExpandedNodesList)
//     //     {
//     //         onTreeViewClicked(node->getModelIndex(), false);
//     //     }
//     // }
//     // else
//     // {
//     //     // 修正动画覆盖
//     //     _navigationView->resize(_pNavigationBarWidth - 5, _navigationView->height());
//     //     for (auto node: _lastExpandedNodesList)
//     //     {
//     //         onTreeViewClicked(node->getModelIndex(), false);
//     //     }
//     // }
// }

// void YyNavigationBarPrivate::_resetLayout()
// {
//     // while (_userButtonLayout->count())
//     // {
//     //     _userButtonLayout->takeAt(0);
//     // }
//     // _userButtonLayout->addWidget(_userButton);
// }

// void YyNavigationBarPrivate::_doNavigationBarWidthAnimation(YyNavigationType::NavigationDisplayMode displayMode, bool isAnimation)
// {
//     // Q_Q(YyNavigationBar);
//     // QPropertyAnimation* navigationBarWidthAnimation = new QPropertyAnimation(q, "maximumWidth");
//     // navigationBarWidthAnimation->setEasingCurve(QEasingCurve::OutCubic);
//     // navigationBarWidthAnimation->setStartValue(q->width());
//     // navigationBarWidthAnimation->setDuration(isAnimation ? 255 : 0);
//     // switch (displayMode)
//     // {
//     // case YyNavigationType::Minimal:
//     // {
//     //     connect(navigationBarWidthAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
//     //         q->setFixedWidth(value.toUInt());
//     //     });
//     //     navigationBarWidthAnimation->setEndValue(0);
//     //     break;
//     // }
//     // case YyNavigationType::Compact:
//     // {
//     //     connect(navigationBarWidthAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
//     //         q->setFixedWidth(value.toUInt());
//     //     });
//     //     navigationBarWidthAnimation->setEndValue(42);
//     //     break;
//     // }
//     // case YyNavigationType::Maximal:
//     // {
//     //     connect(navigationBarWidthAnimation, &QPropertyAnimation::finished, this, [=]() {
//     //         _resetLayout();
//     //     });
//     //     connect(navigationBarWidthAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
//     //         q->setFixedWidth(value.toUInt());
//     //     });
//     //     navigationBarWidthAnimation->setEndValue(_pNavigationBarWidth);
//     //     break;
//     // }
//     // default:
//     // {
//     //     break;
//     // }
//     // }
//     // navigationBarWidthAnimation->start(QAbstractAnimation::DeleteWhenStopped);
// }

// void YyNavigationBarPrivate::_doNavigationViewWidthAnimation(bool isAnimation)
// {
//     // QPropertyAnimation* navigationViewWidthAnimation = new QPropertyAnimation(this, "pNavigationViewWidth");
//     // connect(navigationViewWidthAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
//     //     _navigationView->setColumnWidth(0, value.toUInt());
//     // });
//     // navigationViewWidthAnimation->setEasingCurve(QEasingCurve::OutCubic);
//     // navigationViewWidthAnimation->setStartValue(_navigationView->columnWidth(0));
//     // navigationViewWidthAnimation->setEndValue(40);
//     // navigationViewWidthAnimation->setDuration(isAnimation ? 255 : 0);
//     // navigationViewWidthAnimation->start(QAbstractAnimation::DeleteWhenStopped);
// }

// void YyNavigationBarPrivate::_doUserButtonAnimation(bool isCompact, bool isAnimation)
// {
//     // QPropertyAnimation* userButtonAnimation = new QPropertyAnimation(_userButton, "geometry");
//     // connect(userButtonAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
//     //     _userButton->setFixedSize(value.toRect().size());
//     // });
//     // userButtonAnimation->setEasingCurve(isCompact ? QEasingCurve::OutCubic : QEasingCurve::InOutSine);
//     // QRect maximumRect = QRect(13, 18, 64, 64);
//     // QRect compactRect = QRect(3, 10, 36, 36);
//     // userButtonAnimation->setStartValue(isCompact ? maximumRect : compactRect);
//     // userButtonAnimation->setEndValue(isCompact ? compactRect : maximumRect);

//     // QPropertyAnimation* spacingAnimation = new QPropertyAnimation(this, "pUserButtonSpacing");
//     // connect(spacingAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
//     //     while (_userButtonLayout->count())
//     //     {
//     //         _userButtonLayout->takeAt(0);
//     //     }
//     //     if (_isShowUserCard)
//     //     {
//     //         _userButtonLayout->addSpacing(value.toInt());
//     //     }
//     // });
//     // spacingAnimation->setEasingCurve(isCompact ? QEasingCurve::OutCubic : QEasingCurve::InOutSine);
//     // spacingAnimation->setStartValue(isCompact ? 80 : 36);
//     // spacingAnimation->setEndValue(isCompact ? 36 : 80);
//     // if (isCompact)
//     // {
//     //     _userCard->setVisible(false);
//     //     if (_isShowUserCard)
//     //     {
//     //         _userButton->setVisible(true);
//     //     }
//     //     userButtonAnimation->setDuration(isAnimation ? 255 : 0);
//     //     spacingAnimation->setDuration(isAnimation ? 255 : 0);
//     //     connect(spacingAnimation, &QPropertyAnimation::finished, this, [=]() {
//     //         _resetLayout();
//     //     });
//     // }
//     // else
//     // {
//     //     connect(spacingAnimation, &QPropertyAnimation::finished, this, [=]() {
//     //         _userButton->setFixedSize(64, 64);
//     //         _userButton->setGeometry(QRect(13, 18, 64, 64));
//     //         _userButton->setVisible(false);
//     //         _resetLayout();
//     //         if (_isShowUserCard)
//     //         {
//     //             _userCard->setVisible(true);
//     //         }
//     //     });
//     //     userButtonAnimation->setDuration(isAnimation ? 135 : 0);
//     //     spacingAnimation->setDuration(isAnimation ? 135 : 0);
//     // }
//     // userButtonAnimation->start(QAbstractAnimation::DeleteWhenStopped);
//     // spacingAnimation->start(QAbstractAnimation::DeleteWhenStopped);
// }

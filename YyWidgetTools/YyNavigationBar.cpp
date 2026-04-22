#include "YyNavigationBar.h"

#include "YyBaseListView.h"
#include "YyFooterDelegate.h"
#include "YyFooterModel.h"
#include "YyIconButton.h"
#include "YyInteractiveCard.h"
#include "YyMenu.h"
#include "YyNavigationModel.h"
#include "YyNavigationNode.h"

#include "YyNavigationView.h"
#include "YyTheme.h"
#include "YyToolButton.h"
#include "private/YyNavigationBarPrivate.h"
#include "private/YySuggestBoxPrivate.h"
#include <QEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QResizeEvent>
#include <QScroller>
#include <QVBoxLayout>
Q_PROPERTY_CREATE_Q_CPP(YyNavigationBar, bool, IsTransparent)
Q_PROPERTY_CREATE_Q_CPP(YyNavigationBar, bool, IsAllowPageOpenInNewWindow)
YyNavigationBar::YyNavigationBar(QWidget* parent)
    : QWidget{parent}, d_ptr(new YyNavigationBarPrivate())
{
    Q_D(YyNavigationBar);
    d->q_ptr = this;
    d->_pIsAllowPageOpenInNewWindow = true;
    d->_pNavigationBarWidth = 300;
    setFixedWidth(300);
    d->_pIsTransparent = true;

    //用户卡片
    d->_userCard = new YyInteractiveCard(this);
    d->_userCard->setMinimumWidth(0);
    d->_userCard->setCardPixmap(QPixmap(":/include/Image/Cirno.jpg"));
    d->_userCard->setTitle("Yy Tool");
    d->_userCard->setSubTitle("6666666666@qq.com");
    // connect(d->_userCard, &YyInteractiveCard::clicked, this, &YyNavigationBar::userInfoCardClicked);
    d->_userButton = new YyIconButton(QPixmap(":/include/Image/Cirno.jpg"), this);
    d->_userButton->setFixedSize(36, 36);
    d->_userButton->setVisible(false);
    d->_userButton->setBorderRadius(8);
    d->_userButtonLayout = new QVBoxLayout();
    d->_userButtonLayout->setAlignment(Qt::AlignLeft);
    d->_userButtonLayout->setContentsMargins(0, 0, 0, 0);
    d->_userButtonLayout->setSpacing(0);
    d->_userButtonLayout->addWidget(d->_userButton);

    // connect(d->_userButton, &YyIconButton::clicked, this, &YyNavigationBar::userInfoCardClicked);
    d->_userCardLayout = new QVBoxLayout();
    d->_userCardLayout->setContentsMargins(3, 10, 0, 5);
    d->_userCardLayout->addLayout(d->_userButtonLayout);
    d->_userCardLayout->addWidget(d->_userCard);

    // 搜索跳转
    //    connect(d->_navigationSuggestBox, &YySuggestBox::suggestionClicked, this, [=](QString suggestText, QVariantMap suggestData) {
    //        navigation(suggestData.value("YyPageKey").toString());
    //    });

    // 导航模型
    d->_navigationModel = new YyNavigationModel(this);
    d->_navigationView = new YyNavigationView(this);
    d->_navigationView->setNavigationBarPrivate(d);
    d->_navigationView->setModel(d->_navigationModel);
    connect(d->_navigationView, &YyNavigationView::navigationClicked, this, [=](const QModelIndex& index) {
        d->onTreeViewClicked(index);
    });
    // connect(d->_navigationView, &YyNavigationView::navigationOpenNewWindow, d, &YyNavigationBarPrivate::onNavigationOpenNewWindow);

    // 页脚
    d->_footerView = new YyBaseListView(this);
    d->_footerView->setFixedHeight(0);
    d->_footerModel = new YyFooterModel(this);
    d->_footerView->setModel(d->_footerModel);
    d->_footerDelegate = new YyFooterDelegate(this);
    d->_footerDelegate->setYyListView(d->_footerView);
    d->_footerView->setItemDelegate(d->_footerDelegate);
    connect(d->_footerView, &YyBaseListView::mousePress, this, [=](const QModelIndex& index) {
        d->_footerDelegate->setPressIndex(index);
        d->_footerView->viewport()->update();
    });
    connect(d->_footerView, &YyBaseListView::mouseDoubleClick, this, [=](const QModelIndex& index) {
        d->_footerDelegate->setPressIndex(index);
        d->_footerView->viewport()->update();
    });
    connect(d->_footerView, &YyBaseListView::mouseRelease, this, [=](const QModelIndex& index) {
        d->_footerDelegate->setPressIndex(QModelIndex());
        d->_footerView->viewport()->update();
    });
    connect(d->_footerView, &YyBaseListView::clicked, this, [=](const QModelIndex& index) {
        // d->onFooterViewClicked(index);
    });

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setAlignment(Qt::AlignLeft);
    mainLayout->setSpacing(0);
    mainLayout->addLayout(d->_userCardLayout);

    mainLayout->addWidget(d->_navigationView);
    mainLayout->addWidget(d->_footerView);

    // // 主题设置
    d->_themeMode = eTheme->getThemeMode();
    connect(eTheme, &YyTheme::themeModeChanged, this, [=](YyThemeType::ThemeMode themeMode) {
        d->_themeMode = themeMode;
    });
}

YyNavigationBar::~YyNavigationBar()
{
}

void YyNavigationBar::setNavigationBarWidth(int navigationBarWidth)
{
    Q_D(YyNavigationBar);
    if (navigationBarWidth < 180)
    {
        navigationBarWidth = 180;
    }
    if (d->_currentDisplayMode == YyNavigationType::NavigationDisplayMode::Maximal)
    {
        setFixedWidth(navigationBarWidth);
    }
    d->_pNavigationBarWidth = navigationBarWidth;
    Q_EMIT pNavigationBarWidthChanged();
}

int YyNavigationBar::getNavigationBarWidth() const
{
    Q_D(const YyNavigationBar);
    return d->_pNavigationBarWidth;
}

void YyNavigationBar::setUserInfoCardVisible(bool isVisible)
{
    Q_D(YyNavigationBar);
    d->_isShowUserCard = isVisible;
    if (d->_currentDisplayMode == YyNavigationType::NavigationDisplayMode::Compact)
    {
        d->_userButton->setVisible(isVisible);
    }
    else
    {
        d->_userCard->setVisible(isVisible);
    }
    if (isVisible)
    {
        d->_userCardLayout->setContentsMargins(3, 10, 5, 5);
    }
    else
    {
        d->_userCardLayout->setContentsMargins(0, 0, 0, 0);
    }
}

void YyNavigationBar::setUserInfoCardPixmap(QPixmap pix)
{
    Q_D(YyNavigationBar);
    d->_userCard->setCardPixmap(pix);
    d->_userButton->setPixmap(pix);
}

void YyNavigationBar::setUserInfoCardTitle(QString title)
{
    Q_D(YyNavigationBar);
    d->_userCard->setTitle(title);
}

void YyNavigationBar::setUserInfoCardSubTitle(QString subTitle)
{
    Q_D(YyNavigationBar);
    d->_userCard->setSubTitle(subTitle);
}

YyNavigationType::NodeResult YyNavigationBar::addExpanderNode(const QString &expanderTitle, QString &expanderKey, YyIconType::IconName awesome)
{
    Q_D(YyNavigationBar);
    YyNavigationType::NodeResult result = d->_navigationModel->addExpanderNode(expanderTitle, expanderKey, awesome);
    if(result == YyNavigationType::Success)
    {
        // 传入空ModelIndex默认为根节点
        d->_initNodeModelIndex(QModelIndex());
        //d->_resetNodeSelected();
    }
    return result;
}

YyNavigationType::NodeResult YyNavigationBar::addExpanderNode(const QString &expanderTitle, QString &expanderKey, const QString &targetExpanderKey, YyIconType::IconName awesome)
{
    Q_D(YyNavigationBar);
    YyNavigationType::NodeResult result = d->_navigationModel->addExpanderNode(expanderTitle, expanderKey, targetExpanderKey, awesome);
    if (result == YyNavigationType::Success)
    {
        d->_initNodeModelIndex(QModelIndex());
        //d->_resetNodeSelected();
    }
    return result;
}

YyNavigationType::NodeResult YyNavigationBar::addPageNode(const QString &pageTitle, QWidget *page, YyIconType::IconName awesome)
{
    Q_D(YyNavigationBar);
    if (!page)
    {
        return YyNavigationType::PageInvalid;
    }
    QString pageKey;
    YyNavigationType::NodeResult result = d_ptr->_navigationModel->addPageNode(pageTitle, pageKey, awesome);
    if (result == YyNavigationType::Success)
    {
        d->_pageMetaMap.insert(pageKey, page->metaObject());
        d->_pageNewWindowCountMap.insert(pageKey, 0);
        d->_addStackedPage(page, pageKey);
        d->_initNodeModelIndex(QModelIndex());
        //d->_resetNodeSelected();
    }
    return result;
}

YyNavigationType::NodeResult YyNavigationBar::addPageNode(const QString &pageTitle, QWidget *page, int keyPoints, YyIconType::IconName awesome)
{
    Q_D(YyNavigationBar);
    if (!page)
    {
        return YyNavigationType::PageInvalid;
    }
    QString pageKey;
    YyNavigationType::NodeResult result = d_ptr->_navigationModel->addPageNode(pageTitle, pageKey, keyPoints, awesome);
    if (result == YyNavigationType::Success)
    {
        d->_pageMetaMap.insert(pageKey, page->metaObject());
        d->_pageNewWindowCountMap.insert(pageKey, 0);
        d->_addStackedPage(page, pageKey);
        d->_initNodeModelIndex(QModelIndex());
        //d->_resetNodeSelected();
    }
    return result;
}

YyNavigationType::NodeResult YyNavigationBar::addPageNode(const QString &pageTitle, QWidget *page, const QString &targetExpanderKey, YyIconType::IconName awesome)
{
    Q_D(YyNavigationBar);
    if (!page)
    {
        return YyNavigationType::PageInvalid;
    }
    if (targetExpanderKey.isEmpty())
    {
        return YyNavigationType::TargetNodeInvalid;
    }
    QString pageKey;
    YyNavigationType::NodeResult result = d->_navigationModel->addPageNode(pageTitle, pageKey, targetExpanderKey, awesome);
    if (result == YyNavigationType::NodeResult::Success)
    {
        d->_pageMetaMap.insert(pageKey, page->metaObject());
        d->_pageNewWindowCountMap.insert(pageKey, 0);
        YyNavigationNode* node = d->_navigationModel->getNavigationNode(pageKey);
        YyNavigationNode* originalNode = node->getOriginalNode();
        if (d->_compactMenuMap.contains(originalNode))
        {
            YyMenu* menu = d->_compactMenuMap.value(originalNode);
            QAction* action = menu->addYyIconAction(node->getAwesome(), node->getNodeTitle());
            connect(action, &QAction::triggered, this, [=]() {
                d->onTreeViewClicked(node->getModelIndex());
            });
        }
        else
        {
            YyMenu* menu = new YyMenu(const_cast<YyNavigationBar*>(this));
            QAction* action = menu->addYyIconAction(node->getAwesome(), node->getNodeTitle());
            connect(action, &QAction::triggered, this, [=]() {
                d_ptr->onTreeViewClicked(node->getModelIndex());
            });
            d_ptr->_compactMenuMap.insert(originalNode, menu);
        }
        d_ptr->_addStackedPage(page, pageKey);
        d->_initNodeModelIndex(QModelIndex());
        //d->_resetNodeSelected();
    }
    return result;
}

YyNavigationType::NodeResult YyNavigationBar::addPageNode(const QString &pageTitle, QWidget *page, const QString &targetExpanderKey, int keyPoints, YyIconType::IconName awesome)
{
    Q_D(YyNavigationBar);
    if (!page)
    {
        return YyNavigationType::PageInvalid;
    }
    if (targetExpanderKey.isEmpty())
    {
        return YyNavigationType::TargetNodeInvalid;
    }
    QString pageKey;
    YyNavigationType::NodeResult result = d_ptr->_navigationModel->addPageNode(pageTitle, pageKey, targetExpanderKey, keyPoints, awesome);
    if (result == YyNavigationType::Success)
    {
        d->_pageMetaMap.insert(pageKey, page->metaObject());
        d->_pageNewWindowCountMap.insert(pageKey, 0);
        YyNavigationNode* node = d_ptr->_navigationModel->getNavigationNode(pageKey);
        YyNavigationNode* originalNode = node->getOriginalNode();
        if (d_ptr->_compactMenuMap.contains(originalNode))
        {
            YyMenu* menu = d_ptr->_compactMenuMap.value(originalNode);
            QAction* action = menu->addYyIconAction(node->getAwesome(), node->getNodeTitle());
            connect(action, &QAction::triggered, this, [=]() {
                d_ptr->onTreeViewClicked(node->getModelIndex());
            });
        }
        else
        {
            YyMenu* menu = new YyMenu(const_cast<YyNavigationBar*>(this));
            QAction* action = menu->addYyIconAction(node->getAwesome(), node->getNodeTitle());
            connect(action, &QAction::triggered, this, [=]() {
                d_ptr->onTreeViewClicked(node->getModelIndex());
            });
            d_ptr->_compactMenuMap.insert(originalNode, menu);
        }
        d_ptr->_addStackedPage(page, pageKey);
        d->_initNodeModelIndex(QModelIndex());
        //d->_resetNodeSelected();
    }
    return result;
}

YyNavigationType::NodeResult YyNavigationBar::addFooterNode(const QString &footerTitle, QString &footerKey, int keyPoints, YyIconType::IconName awesome)
{
    return addFooterNode(footerTitle, nullptr, footerKey, keyPoints, awesome);
}

YyNavigationType::NodeResult YyNavigationBar::addFooterNode(const QString &footerTitle, QWidget *page, QString &footerKey, int keyPoints, YyIconType::IconName awesome)
{
    YyNavigationType::NodeResult result = d_ptr->_footerModel->addFooterNode(footerTitle, footerKey, page != nullptr, keyPoints, awesome);
    if (result == YyNavigationType::Success)
    {
        d_ptr->_addFooterPage(page, footerKey);
    }
    return result;
}

YyNavigationType::NodeResult YyNavigationBar::addCategoryNode(const QString &categoryTitle, QString &categoryKey)
{
    Q_D(YyNavigationBar);
    YyNavigationType::NodeResult result = d_ptr->_navigationModel->addCategoryNode(categoryTitle, categoryKey);
    if (result == YyNavigationType::Success)
    {
        d->_initNodeModelIndex(QModelIndex());
        //d->_resetNodeSelected();
        //Q_EMIT navigationNodeAdded(YyNavigationType::CategoryNode, categoryKey, nullptr);
    }
    return result;
}

YyNavigationType::NodeResult YyNavigationBar::addCategoryNode(const QString &categoryTitle, QString &categoryKey, const QString &targetExpanderKey)
{
    Q_D(YyNavigationBar);
    YyNavigationType::NodeResult result = d_ptr->_navigationModel->addCategoryNode(categoryTitle, categoryKey, targetExpanderKey);
    if (result == YyNavigationType::Success)
    {
        d->_initNodeModelIndex(QModelIndex());
        //d->_resetNodeSelected();
    }
    return result;
}

bool YyNavigationBar::getNodeIsExpanded(QString expanderKey) const
{
    Q_D(const YyNavigationBar);
    YyNavigationNode* node = d->_navigationModel->getNavigationNode(expanderKey);
    if (!node || !node->getIsExpanderNode())
    {
        return false;
    }
    return d->_navigationView->isExpanded(node->getModelIndex());
}

void YyNavigationBar::expandNode(QString expanderKey)
{
    Q_D(YyNavigationBar);
    YyNavigationNode* node = d->_navigationModel->getNavigationNode(expanderKey);
    if (!node || !node->getIsExpanderNode())
    {
        return;
    }
    d->_expandOrCollapseExpanderNode(node, true);
    d->_resetNodeSelected();
}

void YyNavigationBar::collapseNode(QString expanderKey)
{
    Q_D(YyNavigationBar);
    YyNavigationNode* node = d->_navigationModel->getNavigationNode(expanderKey);
    if (!node || !node->getIsExpanderNode())
    {
        return;
    }
    d->_expandOrCollapseExpanderNode(node, false);
    d->_resetNodeSelected();
}

void YyNavigationBar::removeNode(QString nodeKey)
{
    Q_D(YyNavigationBar);
    YyNavigationNode* node = d->_navigationModel->getNavigationNode(nodeKey);
    if (!node)
    {
        node = d->_footerModel->getNavigationNode(nodeKey);
    }
    if (!node)
    {
        return;
    }
    if (node->getIsFooterNode())
    {
        Q_EMIT navigationNodeRemoved(YyNavigationType::FooterNode, nodeKey);
        d->_footerModel->removeNavigationNode(nodeKey);
        d->_footerView->setFixedHeight(40 * d->_footerModel->getFooterNodeCount());
    }
    else
    {
        if (node->getIsCategoryNode())
        {
            QStringList removeKeyList = d->_navigationModel->removeNavigationNode(nodeKey);
            d->_initNodeModelIndex(QModelIndex());
            for (const auto& removeKey: removeKeyList)
            {
                Q_EMIT navigationNodeRemoved(YyNavigationType::CategoryNode, removeKey);
            }
        }
        else
        {
            QStringList removeKeyList = d->_navigationModel->removeNavigationNode(nodeKey);
            d->_initNodeModelIndex(QModelIndex());
            for (const auto& removeKey: removeKeyList)
            {
                d->_pageMetaMap.remove(removeKey);
                d->_pageNewWindowCountMap.remove(removeKey);
                Q_EMIT navigationNodeRemoved(YyNavigationType::PageNode, removeKey);
            }
        }
    }
    for (int i = 0; i < d->_suggestDataList.count(); i++)
    {
        auto& suggestData = d->_suggestDataList[i];
        if (suggestData.getSuggestData().value("YyPageKey").toString() == nodeKey)
        {
            d->_suggestDataList.removeAt(i);
            break;
        }
    }
}

void YyNavigationBar::setNodeKeyPoints(QString nodeKey, int keyPoints)
{
    Q_D(YyNavigationBar);
    YyNavigationNode* node = d->_navigationModel->getNavigationNode(nodeKey);
    if (!node)
    {
        node = d->_footerModel->getNavigationNode(nodeKey);
    }
    else if (node->getIsExpanderNode() || keyPoints < 0)
    {
        return;
    }
    if (!node)
    {
        return;
    }
    node->setKeyPoints(keyPoints);
    if (node->getIsFooterNode())
    {
        d->_footerView->viewport()->update();
    }
    else
    {
        d->_navigationView->viewport()->update();
    }
}

int YyNavigationBar::getNodeKeyPoints(QString nodeKey) const
{
    Q_D(const YyNavigationBar);
    YyNavigationNode* node = d->_navigationModel->getNavigationNode(nodeKey);
    if (!node)
    {
        node = d->_footerModel->getNavigationNode(nodeKey);
    }
    else if (node->getIsExpanderNode())
    {
        return -1;
    }
    if (!node)
    {
        return -1;
    }
    return node->getKeyPoints();
}

void YyNavigationBar::setNodeTitle(QString nodeKey, QString nodeTitle)
{
    Q_D(YyNavigationBar);
    YyNavigationNode* node = d->_navigationModel->getNavigationNode(nodeKey);
    if (!node)
    {
        node = d->_footerModel->getNavigationNode(nodeKey);
    }
    if (!node)
    {
        return;
    }
    node->setNodeTitle(nodeTitle);
    update();
}

QString YyNavigationBar::getNodeTitle(QString nodeKey) const
{
    Q_D(const YyNavigationBar);
    YyNavigationNode* node = d->_navigationModel->getNavigationNode(nodeKey);
    if (!node)
    {
        node = d->_footerModel->getNavigationNode(nodeKey);
    }
    if (!node)
    {
        return {};
    }
    return node->getNodeTitle();
}

void YyNavigationBar::navigation(QString pageKey, bool isLogClicked, bool isRouteBack)
{
    Q_D(YyNavigationBar);
    YyNavigationNode* node = d->_navigationModel->getNavigationNode(pageKey);
    if (!node)
    {
        node = d->_footerModel->getNavigationNode(pageKey);
    }
    if (node)
    {
        if (node->getIsFooterNode())
        {
            d->onFooterViewClicked(node->getModelIndex(), isLogClicked, isRouteBack);
        }
        else
        {
            if (!node->getIsExpanderNode())
            {
                d->onTreeViewClicked(node->getModelIndex(), isLogClicked, isRouteBack);
                //d->_smoothScrollNavigationView(node->getModelIndex());
            }
        }
    }
}

void YyNavigationBar::setDisplayMode(YyNavigationType::NavigationDisplayMode displayMode, bool isAnimation)
{
    Q_D(YyNavigationBar);
    if (d->_currentDisplayMode == displayMode || displayMode == YyNavigationType::Auto)
    {
        return;
    }
    d->_navigationModel->setIsMaximalMode(displayMode == YyNavigationType::Maximal);
   // d->_doComponentAnimation(displayMode, isAnimation);
    d->_raiseNavigationBar();
}

YyNavigationType::NavigationDisplayMode YyNavigationBar::getDisplayMode() const
{
    Q_D(const YyNavigationBar);
    return d->_currentDisplayMode;
}

int YyNavigationBar::getPageOpenInNewWindowCount(QString nodeKey) const
{
    Q_D(const YyNavigationBar);
    if (!d->_pageNewWindowCountMap.contains(nodeKey))
    {
        return 0;
    }
    return d->_pageNewWindowCountMap[nodeKey];
}

QList<YySuggestBox::SuggestData> YyNavigationBar::getSuggestDataList() const
{
    Q_D(const YyNavigationBar);
    return d->_suggestDataList;
}



void YyNavigationBar::paintEvent(QPaintEvent* event)
{
    Q_D(YyNavigationBar);
    if (!d->_pIsTransparent)
    {
        QPainter painter(this);
        painter.save();
        painter.setPen(YyThemeColor(d->_themeMode, PopupBorder));
        painter.setBrush(YyThemeColor(d->_themeMode, PopupBase));
        QRect baseRect = this->rect();
        baseRect.adjust(-1, 0, -1, 0);
        QPainterPath path;
        path.moveTo(baseRect.topLeft());
        path.lineTo(QPoint(baseRect.right() - 8, baseRect.y()));
        path.arcTo(QRectF(baseRect.right() - 16, baseRect.y(), 16, 16), 90, -90);
        path.lineTo(QPoint(baseRect.right(), baseRect.bottom() - 8));
        path.arcTo(QRectF(baseRect.right() - 16, baseRect.bottom() - 16, 16, 16), 0, -90);
        path.lineTo(baseRect.bottomLeft());
        path.closeSubpath();
        painter.drawPath(path);
        painter.restore();
    }
    QWidget::paintEvent(event);
}

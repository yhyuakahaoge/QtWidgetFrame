#ifndef YyNAVIGATIONBAR_H
#define YyNAVIGATIONBAR_H

#include <QWidget>

#include "YyDef.h"
#include "YyProperty.h"
//#include "YySuggestBox.h"
class YyNavigationBarPrivate;
class Yy_EXPORT YyNavigationBar : public QWidget
{
    Q_OBJECT
    Q_Q_CREATE(YyNavigationBar)
    Q_PROPERTY_CREATE_Q_H(bool, IsTransparent)
    // Q_PROPERTY_CREATE_Q_H(bool, IsAllowPageOpenInNewWindow)
    Q_PROPERTY_CREATE_Q_H(int, NavigationBarWidth)
public:
    explicit YyNavigationBar(QWidget* parent = nullptr);
    ~YyNavigationBar() override;
    void setUserInfoCardVisible(bool isVisible);
    void setUserInfoCardPixmap(QPixmap pix);
    void setUserInfoCardTitle(QString title);
    void setUserInfoCardSubTitle(QString subTitle);

    // YyNavigationType::NodeResult addExpanderNode(const QString& expanderTitle, QString& expanderKey, YyIconType::IconName awesome = YyIconType::None);
    // YyNavigationType::NodeResult addExpanderNode(const QString& expanderTitle, QString& expanderKey, const QString& targetExpanderKey, YyIconType::IconName awesome = YyIconType::None);
    // YyNavigationType::NodeResult addPageNode(const QString& pageTitle, QWidget* page, YyIconType::IconName awesome = YyIconType::None);
    // YyNavigationType::NodeResult addPageNode(const QString& pageTitle, QWidget* page, int keyPoints, YyIconType::IconName awesome = YyIconType::None);
    // YyNavigationType::NodeResult addPageNode(const QString& pageTitle, QWidget* page, const QString& targetExpanderKey, YyIconType::IconName awesome = YyIconType::None);
    // YyNavigationType::NodeResult addPageNode(const QString& pageTitle, QWidget* page, const QString& targetExpanderKey, int keyPoints, YyIconType::IconName awesome = YyIconType::None);
    // YyNavigationType::NodeResult addFooterNode(const QString& footerTitle, QString& footerKey, int keyPoints = 0, YyIconType::IconName awesome = YyIconType::None);
    // YyNavigationType::NodeResult addFooterNode(const QString& footerTitle, QWidget* page, QString& footerKey, int keyPoints = 0, YyIconType::IconName awesome = YyIconType::None);
    // YyNavigationType::NodeResult addCategoryNode(const QString& categoryTitle, QString& categoryKey);
    // YyNavigationType::NodeResult addCategoryNode(const QString& categoryTitle, QString& categoryKey, const QString& targetExpanderKey);

    // bool getNodeIsExpanded(QString expanderKey) const;
    // void expandNode(QString expanderKey);
    // void collapseNode(QString expanderKey);
    // void removeNode(QString nodeKey);

    // void setNodeKeyPoints(QString nodeKey, int keyPoints);
    // int getNodeKeyPoints(QString nodeKey) const;

    // void setNodeTitle(QString nodeKey, QString nodeTitle);
    // QString getNodeTitle(QString nodeKey) const;

    // void navigation(QString pageKey, bool isLogClicked = true, bool isRouteBack = false);
    // void setDisplayMode(YyNavigationType::NavigationDisplayMode displayMode, bool isAnimation = true);
    // YyNavigationType::NavigationDisplayMode getDisplayMode() const;

    // int getPageOpenInNewWindowCount(QString nodeKey) const;

    // QList<YySuggestBox::SuggestData> getSuggestDataList() const;

Q_SIGNALS:
    Q_SIGNAL void pageOpenInNewWindow(QString nodeKey);
    Q_SIGNAL void userInfoCardClicked();
    Q_SIGNAL void navigationNodeClicked(YyNavigationType::NavigationNodeType nodeType, QString nodeKey, bool isRouteBack);
    Q_SIGNAL void navigationNodeAdded(YyNavigationType::NavigationNodeType nodeType, QString nodeKey, QWidget* page);
    Q_SIGNAL void navigationNodeRemoved(YyNavigationType::NavigationNodeType nodeType, QString nodeKey);

protected:
    virtual void paintEvent(QPaintEvent* event) override;
};

#endif // YyNAVIGATIONBAR_H

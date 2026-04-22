#ifndef YyNAVIGATIONNODE_H
#define YyNAVIGATIONNODE_H

#include <QModelIndex>
#include <QObject>

#include "YyDef.h"

class YyNavigationNode : public QObject
{
    Q_OBJECT
    Q_PRIVATE_CREATE(QList<YyNavigationNode*>, ChildrenNodes)
    Q_PRIVATE_CREATE(YyNavigationNode*, ParentNode)
    Q_PRIVATE_CREATE(YyIconType::IconName, Awesome)
    Q_PRIVATE_REF_CREATE(QModelIndex, ModelIndex)
    Q_PRIVATE_CREATE(int, KeyPoints)
    Q_PRIVATE_CREATE(int, Depth)
    Q_PRIVATE_CREATE(bool, IsRootNode)
    Q_PRIVATE_CREATE(bool, IsFooterNode)
    Q_PRIVATE_CREATE(bool, IsHasFooterPage)
    Q_PRIVATE_CREATE(bool, IsExpanderNode)
    Q_PRIVATE_CREATE(bool, IsCategoryNode)
    Q_PRIVATE_CREATE(bool, IsVisible)
    Q_PRIVATE_CREATE(QString, NodeTitle)
public:
    explicit YyNavigationNode(const QString& nodeTitle, YyNavigationNode* parent = nullptr);
    ~YyNavigationNode() override;

    QString getNodeKey() const;

    void setIsExpanded(bool isExpanded);
    bool getIsExpanded() const;

    void setChildVisible(bool isVisible);
    bool getIsHasChild() const;
    bool getIsHasPageChild() const;

    void appendChildNode(YyNavigationNode* childNode);
    void removeChildNode(YyNavigationNode* childNode);

    bool getIsChildHasKeyPoints() const;

    YyNavigationNode* getOriginalNode();
    bool getIsChildNode(YyNavigationNode* node);

    int getRow() const;

    QList<YyNavigationNode*> getExceptCategoryNodes();

private:
    QString _nodeKey = "";
    bool _isExpanded{false};
};

#endif // YyNAVIGATIONNODE_H

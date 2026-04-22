#include "YyNavigationModel.h"

#include <QIcon>
#include <QJsonObject>

#include "YyNavigationNode.h"
YyNavigationModel::YyNavigationModel(QObject* parent)
    : QAbstractItemModel{parent}
{
    _rootNode = new YyNavigationNode("root");
    _rootNode->setIsRootNode(true);
    _rootNode->setIsExpanderNode(true);
    _pSelectedNode = nullptr;
    _pSelectedExpandedNode = nullptr;
}

YyNavigationModel::~YyNavigationModel()
{
    delete _rootNode;
}

void YyNavigationModel::setIsMaximalMode(bool isMaximal)
{
    auto rootNodes = _rootNode->getChildrenNodes();
    for (int i = 0; i < rootNodes.count(); i++)
    {
        auto childNode = rootNodes[i];
        if (childNode->getIsCategoryNode())
        {
            if (!isMaximal)
            {
                beginRemoveRows({}, i, i);
                _isMaximalMode = isMaximal;
                endRemoveRows();
            }
            else
            {
                beginInsertRows({}, i, i);
                _isMaximalMode = isMaximal;
                endInsertRows();
            }
        }
    }
}

bool YyNavigationModel::getIsMaximalMode()
{
    return _isMaximalMode;
}

QModelIndex YyNavigationModel::parent(const QModelIndex& child) const
{
    if (!child.isValid())
    {
        return {};
    }
    YyNavigationNode* childNode = static_cast<YyNavigationNode*>(child.internalPointer());
    YyNavigationNode* parentNode = childNode->getParentNode();
    if (parentNode == _rootNode)
    {
        return {};
    }
    if (parentNode == nullptr)
    {
        return {};
    }
    return createIndex(parentNode->getRow(), 0, parentNode);
}

QModelIndex YyNavigationModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return {};
    }
    YyNavigationNode* parentNode;
    if (!parent.isValid())
    {
        parentNode = _rootNode;
    }
    else
    {
        parentNode = static_cast<YyNavigationNode*>(parent.internalPointer());
    }
    YyNavigationNode* childNode = nullptr;
    if (parentNode->getChildrenNodes().count() > row)
    {
        if (parentNode == _rootNode && !_isMaximalMode)
        {
            childNode = parentNode->getExceptCategoryNodes().at(row);
        }
        else
        {
            childNode = parentNode->getChildrenNodes().at(row);
        }
    }
    if (childNode)
    {
        childNode->setModelIndex(createIndex(row, column, childNode));
        return childNode->getModelIndex();
    }
    return {};
}

int YyNavigationModel::rowCount(const QModelIndex& parent) const
{
    YyNavigationNode* parentNode;
    if (parent.column() > 0)
    {
        return 0;
    }
    if (!parent.isValid())
    {
        parentNode = _rootNode;
    }
    else
    {
        parentNode = static_cast<YyNavigationNode*>(parent.internalPointer());
    }
    if (parentNode == _rootNode && !_isMaximalMode)
    {
        return _rootNode->getExceptCategoryNodes().count();
    }
    return parentNode->getChildrenNodes().count();
};

int YyNavigationModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 1;
}

QVariant YyNavigationModel::data(const QModelIndex& index, int role) const
{
    Q_UNUSED(index)
    Q_UNUSED(role)
    return QVariant();
}

// 根节点插入
YyNavigationType::NodeResult YyNavigationModel::addExpanderNode(const QString& expanderTitle, QString& expanderKey, YyIconType::IconName awesome)
{
    YyNavigationNode* node = new YyNavigationNode(expanderTitle, _rootNode);
    node->setDepth(1);
    node->setIsVisible(true);
    node->setIsExpanderNode(true);
    node->setAwesome(awesome);
    beginInsertRows(QModelIndex(), _rootNode->getChildrenNodes().count(), _rootNode->getChildrenNodes().count());
    _rootNode->appendChildNode(node);
    //NodeKey为每个节点的UUID
    _nodesMap.insert(node->getNodeKey(), node);
    endInsertRows();
    expanderKey = node->getNodeKey();
    return YyNavigationType::NodeResult::Success;
}

// 指定节点插入
YyNavigationType::NodeResult YyNavigationModel::addExpanderNode(const QString& expanderTitle, QString& expanderKey, const QString& targetExpanderKey, YyIconType::IconName awesome)
{
    if (!_nodesMap.contains(targetExpanderKey))
    {
        return YyNavigationType::NodeResult::TargetNodeInvalid;
    }
    YyNavigationNode* parentNode = _nodesMap.value(targetExpanderKey);
    if (!parentNode->getIsExpanderNode())
    {
        return YyNavigationType::NodeResult::TargetNodeTypeError;
    }
    if (parentNode->getDepth() > 10)
    {
        return YyNavigationType::NodeResult::TargetNodeDepthLimit;
    }
    YyNavigationNode* node = new YyNavigationNode(expanderTitle, parentNode);
    node->setDepth(parentNode->getDepth() + 1);
    node->setIsExpanderNode(true);
    node->setAwesome(awesome);
    if (parentNode->getIsVisible() && parentNode->getIsExpanded())
    {
        node->setIsVisible(true);
    }
    beginInsertRows(parentNode->getModelIndex(), parentNode->getChildrenNodes().count(), parentNode->getChildrenNodes().count());
    parentNode->appendChildNode(node);
    _nodesMap.insert(node->getNodeKey(), node);
    endInsertRows();
    expanderKey = node->getNodeKey();
    return YyNavigationType::NodeResult::Success;
}

YyNavigationType::NodeResult YyNavigationModel::addPageNode(const QString& pageTitle, QString& pageKey, YyIconType::IconName awesome)
{
    YyNavigationNode* node = new YyNavigationNode(pageTitle, _rootNode);
    node->setAwesome(awesome);
    node->setDepth(1);
    node->setIsVisible(true);
    beginInsertRows(QModelIndex(), _rootNode->getChildrenNodes().count(), _rootNode->getChildrenNodes().count());
    _rootNode->appendChildNode(node);
    _nodesMap.insert(node->getNodeKey(), node);
    endInsertRows();
    pageKey = node->getNodeKey();
    if (!_pSelectedNode)
    {
        _pSelectedNode = node;
    }
    return YyNavigationType::NodeResult::Success;
}

YyNavigationType::NodeResult YyNavigationModel::addPageNode(const QString& pageTitle, QString& pageKey, const QString& targetExpanderKey, YyIconType::IconName awesome)
{
    if (!_nodesMap.contains(targetExpanderKey))
    {
        return YyNavigationType::NodeResult::TargetNodeInvalid;
    }
    YyNavigationNode* parentNode = _nodesMap.value(targetExpanderKey);
    if (!parentNode->getIsExpanderNode())
    {
        return YyNavigationType::NodeResult::TargetNodeTypeError;
    }
    if (parentNode->getDepth() > 10)
    {
        return YyNavigationType::NodeResult::TargetNodeDepthLimit;
    }
    YyNavigationNode* node = new YyNavigationNode(pageTitle, parentNode);
    node->setDepth(parentNode->getDepth() + 1);
    node->setAwesome(awesome);
    if (parentNode->getIsVisible() && parentNode->getIsExpanded())
    {
        node->setIsVisible(true);
    }
    beginInsertRows(parentNode->getModelIndex(), parentNode->getChildrenNodes().count(), parentNode->getChildrenNodes().count());
    parentNode->appendChildNode(node);
    _nodesMap.insert(node->getNodeKey(), node);
    endInsertRows();
    pageKey = node->getNodeKey();
    if (!_pSelectedNode)
    {
        _pSelectedNode = node;
    }
    return YyNavigationType::NodeResult::Success;
}

YyNavigationType::NodeResult YyNavigationModel::addPageNode(const QString& pageTitle, QString& pageKey, int keyPoints, YyIconType::IconName awesome)
{
    YyNavigationNode* node = new YyNavigationNode(pageTitle, _rootNode);
    node->setAwesome(awesome);
    node->setDepth(1);
    node->setIsVisible(true);
    node->setKeyPoints(keyPoints);
    beginInsertRows(QModelIndex(), _rootNode->getChildrenNodes().count(), _rootNode->getChildrenNodes().count());
    _rootNode->appendChildNode(node);
    _nodesMap.insert(node->getNodeKey(), node);
    endInsertRows();
    pageKey = node->getNodeKey();
    if (!_pSelectedNode)
    {
        _pSelectedNode = node;
    }
    return YyNavigationType::NodeResult::Success;
}

YyNavigationType::NodeResult YyNavigationModel::addPageNode(const QString& pageTitle, QString& pageKey, const QString& targetExpanderKey, int keyPoints, YyIconType::IconName awesome)
{
    if (!_nodesMap.contains(targetExpanderKey))
    {
        return YyNavigationType::NodeResult::TargetNodeInvalid;
    }
    YyNavigationNode* parentNode = _nodesMap.value(targetExpanderKey);
    if (!parentNode->getIsExpanderNode())
    {
        return YyNavigationType::NodeResult::TargetNodeTypeError;
    }
    if (parentNode->getDepth() > 10)
    {
        return YyNavigationType::NodeResult::TargetNodeDepthLimit;
    }
    YyNavigationNode* node = new YyNavigationNode(pageTitle, parentNode);
    node->setDepth(parentNode->getDepth() + 1);
    node->setAwesome(awesome);
    node->setKeyPoints(keyPoints);
    if (parentNode->getIsVisible() && parentNode->getIsExpanded())
    {
        node->setIsVisible(true);
    }
    beginInsertRows(parentNode->getModelIndex(), parentNode->getChildrenNodes().count(), parentNode->getChildrenNodes().count());
    parentNode->appendChildNode(node);
    _nodesMap.insert(node->getNodeKey(), node);
    endInsertRows();
    pageKey = node->getNodeKey();
    if (!_pSelectedNode)
    {
        _pSelectedNode = node;
    }
    return YyNavigationType::NodeResult::Success;
}

YyNavigationType::NodeResult YyNavigationModel::addCategoryNode(const QString& categoryTitle, QString& categoryKey)
{
    YyNavigationNode* node = new YyNavigationNode(categoryTitle, _rootNode);
    node->setDepth(1);
    node->setIsVisible(true);
    node->setIsCategoryNode(true);
    beginInsertRows(QModelIndex(), _rootNode->getChildrenNodes().count(), _rootNode->getChildrenNodes().count());
    _rootNode->appendChildNode(node);
    _nodesMap.insert(node->getNodeKey(), node);
    endInsertRows();
    categoryKey = node->getNodeKey();
    return YyNavigationType::NodeResult::Success;
}

YyNavigationType::NodeResult YyNavigationModel::addCategoryNode(const QString& categoryTitle, QString& categoryKey, const QString& targetExpanderKey)
{
    if (!_nodesMap.contains(targetExpanderKey))
    {
        return YyNavigationType::NodeResult::TargetNodeInvalid;
    }
    YyNavigationNode* parentNode = _nodesMap.value(targetExpanderKey);
    if (!parentNode->getIsExpanderNode())
    {
        return YyNavigationType::NodeResult::TargetNodeTypeError;
    }
    if (parentNode->getDepth() > 10)
    {
        return YyNavigationType::NodeResult::TargetNodeDepthLimit;
    }
    YyNavigationNode* node = new YyNavigationNode(categoryTitle, parentNode);
    node->setDepth(parentNode->getDepth() + 1);
    node->setIsCategoryNode(true);
    if (parentNode->getIsVisible() && parentNode->getIsExpanded())
    {
        node->setIsVisible(true);
    }
    beginInsertRows(parentNode->getModelIndex(), parentNode->getChildrenNodes().count(), parentNode->getChildrenNodes().count());
    parentNode->appendChildNode(node);
    _nodesMap.insert(node->getNodeKey(), node);
    endInsertRows();
    categoryKey = node->getNodeKey();
    return YyNavigationType::NodeResult::Success;
}

//删除非可展开节点，递归删除可展开节点下所有节点
QStringList YyNavigationModel::removeNavigationNode(const QString& nodeKey)
{
    QList<QString> removeKeyList;
    if (!_nodesMap.contains(nodeKey))
    {
        return removeKeyList;
    }
    YyNavigationNode* node = _nodesMap.value(nodeKey);
    YyNavigationNode* parentNode = node->getParentNode();
    if (node->getIsExpanderNode())
    {
        QList<YyNavigationNode*> childNodeList = node->getChildrenNodes();
        for (int i = 0; i < childNodeList.count(); i++)
        {
            YyNavigationNode* childNode = childNodeList[i];
            QList<QString> childRemoveKeyList = removeNavigationNode(childNode->getNodeKey());
            removeKeyList.append(childRemoveKeyList);
        }
    }
    else
    {
        removeKeyList.append(node->getNodeKey());
    }
    _nodesMap.remove(node->getNodeKey());
    int removeRow = parentNode->getChildrenNodes().indexOf(node);
    beginRemoveRows(parentNode->getModelIndex(), removeRow, removeRow);
    parentNode->removeChildNode(node);
    endRemoveRows();
    node->deleteLater();
    return removeKeyList;
}

YyNavigationNode* YyNavigationModel::getNavigationNode(const QString& nodeKey) const
{
    if (_nodesMap.contains(nodeKey))
    {
        return _nodesMap.value(nodeKey);
    }
    return nullptr;
}

QList<YyNavigationNode*> YyNavigationModel::getRootExpanderNodes() const
{
    QList<YyNavigationNode*> expandedNodeList;
    for (auto node: _rootNode->getChildrenNodes())
    {
        if (node->getIsExpanderNode())
        {
            expandedNodeList.append(node);
        }
    }
    return expandedNodeList;
}

QList<YyNavigationNode*> YyNavigationModel::getRootExpandedNodes() const
{
    QList<YyNavigationNode*> expandedNodeList;
    for (auto node: _rootNode->getChildrenNodes())
    {
        if (node->getIsExpanderNode() && node->getIsExpanded())
        {
            expandedNodeList.append(node);
        }
    }
    return expandedNodeList;
}

QList<YyNavigationNode*> YyNavigationModel::getRootCategoryNodes() const
{
    QList<YyNavigationNode*> categoryNodeList;
    for (auto node: _rootNode->getChildrenNodes())
    {
        if (node->getIsCategoryNode())
        {
            categoryNodeList.append(node);
        }
    }
    return categoryNodeList;
}

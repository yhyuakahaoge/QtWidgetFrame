#include "YyNavigationNode.h"

#include <QUuid>

YyNavigationNode::YyNavigationNode(const QString& nodeTitle, YyNavigationNode* parent)
    : QObject(parent)
{
    _pDepth = 0;
    _pKeyPoints = 0;
    _nodeKey = QUuid::createUuid().toString().remove("{").remove("}").remove("-");
    _pNodeTitle = nodeTitle;
    _pIsRootNode = false;
    _pIsFooterNode = false;
    _pIsHasFooterPage = false;
    _pParentNode = parent;
    _pIsExpanderNode = false;
    _pIsVisible = false;
    _pIsCategoryNode = false;
    _pAwesome = YyIconType::None;
}

YyNavigationNode::~YyNavigationNode()
{
}

QString YyNavigationNode::getNodeKey() const
{
    return _nodeKey;
}

void YyNavigationNode::setIsExpanded(bool isExpanded)
{
    _isExpanded = isExpanded;
    setChildVisible(isExpanded);
}

bool YyNavigationNode::getIsExpanded() const
{
    return _isExpanded;
}

void YyNavigationNode::setChildVisible(bool isVisible)
{
    if (isVisible)
    {
        for (auto node: _pChildrenNodes)
        {
            node->setIsVisible(isVisible);
            if (node->getIsExpanderNode() && !node->getIsExpanded())
            {
                continue;
            }
            node->setChildVisible(isVisible);
        }
    }
    else
    {
        for (auto node: _pChildrenNodes)
        {
            node->setChildVisible(isVisible);
            node->setIsVisible(isVisible);
        }
    }
}

bool YyNavigationNode::getIsHasChild() const
{
    if (_pChildrenNodes.count() > 0)
    {
        return true;
    }
    return false;
}

bool YyNavigationNode::getIsHasPageChild() const
{
    if (_pChildrenNodes.count() == 0)
    {
        return false;
    }
    for (auto childNode: _pChildrenNodes)
    {
        if (!childNode->getIsExpanderNode())
        {
            return true;
        }
        if (childNode->getIsHasPageChild())
        {
            return true;
        }
    }
    return false;
}

void YyNavigationNode::appendChildNode(YyNavigationNode* childNode)
{
    if (_pIsExpanderNode)
    {
        _pChildrenNodes.append(childNode);
    }
}

void YyNavigationNode::removeChildNode(YyNavigationNode* childNode)
{
    if (_pIsExpanderNode)
    {
        _pChildrenNodes.removeOne(childNode);
    }
}

bool YyNavigationNode::getIsChildHasKeyPoints() const
{
    for (auto childNnode: _pChildrenNodes)
    {
        if (childNnode->getKeyPoints())
        {
            return true;
        }
        if (childNnode->getIsChildHasKeyPoints())
        {
            return true;
        }
    }
    return false;
}

YyNavigationNode* YyNavigationNode::getOriginalNode()
{
    if (this->getParentNode()->getIsRootNode())
    {
        return this;
    }
    else
    {
        YyNavigationNode* originalNode = this->getParentNode();
        while (!originalNode->getIsRootNode() && !originalNode->getParentNode()->getIsRootNode())
        {
            originalNode = originalNode->getParentNode();
        }
        return originalNode;
    }
}

bool YyNavigationNode::getIsChildNode(YyNavigationNode* node)
{
    if (_pChildrenNodes.count() > 0)
    {
        if (_pChildrenNodes.contains(node))
        {
            return true;
        }
        //for (auto childNnode: _pChildrenNodes)
        for (auto it = _pChildrenNodes.cbegin(); it != _pChildrenNodes.cend(); it++)
        {
            auto childNnode = *it;
            if (childNnode->getIsChildNode(node))
            {
                return true;
            }
        }
    }
    return false;
}

int YyNavigationNode::getRow() const
{
    if (_pParentNode)
    {
        return _pParentNode->getChildrenNodes().indexOf(const_cast<YyNavigationNode*>(this));
    }
    return 0;
}

QList<YyNavigationNode*> YyNavigationNode::getExceptCategoryNodes()
{
    QList<YyNavigationNode*> exceptCategoryNodeList;
    //for (const auto node: _pChildrenNodes)
    for (auto it = _pChildrenNodes.cbegin(); it != _pChildrenNodes.cend(); it ++)
    {
        auto node = *it;
        if (!node->getIsCategoryNode())
        {
            exceptCategoryNodeList.append(node);
        }
    }
    return exceptCategoryNodeList;
}

#include "YyFooterModel.h"

#include <QUuid>

#include "YyNavigationNode.h"
YyFooterModel::YyFooterModel(QObject* parent)
    : QAbstractListModel{parent}
{
    _pSelectedNode = nullptr;
}

YyFooterModel::~YyFooterModel()
{
    qDeleteAll(_footerNodeList);
}

int YyFooterModel::rowCount(const QModelIndex& parent) const
{
    return _footerNodeList.count();
}

QVariant YyFooterModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::UserRole)
    {
        if (index.row() < _footerNodeList.count())
        {
            return QVariant::fromValue(_footerNodeList[index.row()]);
        }
    }
    return QVariant();
}

YyNavigationType::NodeResult YyFooterModel::addFooterNode(QString footerTitle, QString& footerKey, bool isHasFooterPage, int keyPoints, YyIconType::IconName awesome)
{
    // 底部只允许两个Foot节点
    if (_footerNodeList.count() >= 3)
    {
        return YyNavigationType::FooterUpperLimit;
    }
    YyNavigationNode* node = new YyNavigationNode(footerTitle);
    node->setKeyPoints(keyPoints);
    node->setIsFooterNode(true);
    node->setIsHasFooterPage(isHasFooterPage);
    node->setAwesome(awesome);
    footerKey = node->getNodeKey();
    beginResetModel();
    _footerNodeList.append(node);
    endResetModel();
    node->setModelIndex(this->index(_footerNodeList.count() - 1));
    return YyNavigationType::Success;
}

int YyFooterModel::getFooterNodeCount() const
{
    return _footerNodeList.count();
}

YyNavigationNode* YyFooterModel::getNavigationNode(QString footerKey)
{
    for (auto node: _footerNodeList)
    {
        if (node->getNodeKey() == footerKey)
        {
            return node;
        }
    }
    return nullptr;
}

void YyFooterModel::removeNavigationNode(QString footerKey)
{
    for (auto node: _footerNodeList)
    {
        if (node->getNodeKey() == footerKey)
        {
            _footerNodeList.removeOne(node);
            break;
        }
    }
}

#ifndef YyNAVIGATIONMODEL_H
#define YyNAVIGATIONMODEL_H

#include <QAbstractItemModel>
#include <QObject>

#include "YyDef.h"
class YyNavigationNode;
class YyNavigationModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_PRIVATE_CREATE(YyNavigationNode*, SelectedNode)
    Q_PRIVATE_CREATE(YyNavigationNode*, SelectedExpandedNode)

public:
    explicit YyNavigationModel(QObject* parent = nullptr);
    ~YyNavigationModel() override;

    void setIsMaximalMode(bool isMaximal);
    bool getIsMaximalMode();

    virtual QModelIndex parent(const QModelIndex& child) const override;
    virtual QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    YyNavigationType::NodeResult addExpanderNode(const QString& expanderTitle, QString& expanderKey, YyIconType::IconName awesome);
    YyNavigationType::NodeResult addExpanderNode(const QString& expanderTitle, QString& expanderKey, const QString& targetExpanderKey, YyIconType::IconName awesome);
    YyNavigationType::NodeResult addPageNode(const QString& pageTitle, QString& pageKey, YyIconType::IconName awesome);
    YyNavigationType::NodeResult addPageNode(const QString& pageTitle, QString& pageKey, const QString& targetExpanderKey, YyIconType::IconName awesome);
    YyNavigationType::NodeResult addPageNode(const QString& pageTitle, QString& pageKey, int keyPoints, YyIconType::IconName awesome);
    YyNavigationType::NodeResult addPageNode(const QString& pageTitle, QString& pageKey, const QString& targetExpanderKey, int keyPoints, YyIconType::IconName awesome);
    YyNavigationType::NodeResult addCategoryNode(const QString& categoryTitle, QString& categoryKey);
    YyNavigationType::NodeResult addCategoryNode(const QString& categoryTitle, QString& categoryKey, const QString& targetExpanderKey);

    QStringList removeNavigationNode(const QString& nodeKey);

    YyNavigationNode* getNavigationNode(const QString& nodeKey) const;
    QList<YyNavigationNode*> getRootExpanderNodes() const;
    QList<YyNavigationNode*> getRootExpandedNodes() const;

    QList<YyNavigationNode*> getRootCategoryNodes() const;

private:
    bool _isMaximalMode{true};
    QMap<QString, YyNavigationNode*> _nodesMap;
    YyNavigationNode* _rootNode{nullptr};
};

#endif // YyNAVIGATIONMODEL_H

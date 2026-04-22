#ifndef YyFOOTERMODEL_H
#define YyFOOTERMODEL_H

#include <QAbstractListModel>

#include "YyDef.h"
class YyNavigationNode;
class YyFooterModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PRIVATE_CREATE(YyNavigationNode*, SelectedNode)
public:
    explicit YyFooterModel(QObject* parent = nullptr);
    ~YyFooterModel();
    YyNavigationType::NodeResult addFooterNode(QString footerTitle, QString& footerKey, bool isHasFooterPage, int keyPoints = 0, YyIconType::IconName awesome = YyIconType::None);
    int getFooterNodeCount() const;
    YyNavigationNode* getNavigationNode(QString footerKey);
    void removeNavigationNode(QString footerKey);

protected:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;

private:
    QList<YyNavigationNode*> _footerNodeList;
};

#endif // YyFOOTERMODEL_H

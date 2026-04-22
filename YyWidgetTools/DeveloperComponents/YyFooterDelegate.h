#ifndef YyFOOTERDELEGATE_H
#define YyFOOTERDELEGATE_H

#include <QModelIndex>
#include <QStyledItemDelegate>

#include "YyDef.h"
class YyNavigationNode;
class QPropertyAnimation;
class YyBaseListView;
class YyFooterDelegate : public QStyledItemDelegate
{
    Q_OBJECT
    Q_PRIVATE_CREATE(YyBaseListView*, YyListView);
    Q_PRIVATE_CREATE(QModelIndex, PressIndex);

public:
    explicit YyFooterDelegate(QObject* parent = nullptr);
    ~YyFooterDelegate();
    void navigationNodeStateChange(QVariantMap data);

protected:
    virtual void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    virtual QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

private:
    int _leftPadding{11};
    int _iconAreaWidth{40};
    int _textRightSpacing{3};
    int _indicatorIconAreaWidth{24};
    qreal _lastSelectMarkTop{10};
    qreal _lastSelectMarkBottom{10};
    qreal _selectMarkTop{10};
    qreal _selectMarkBottom{10};
    bool _isSelectMarkDisplay{true};
    YyNavigationNode* _lastSelectedNode{nullptr};
    YyThemeType::ThemeMode _themeMode;
    QPropertyAnimation* _lastSelectMarkTopAnimation{nullptr};
    QPropertyAnimation* _lastSelectMarkBottomAnimation{nullptr};
    QPropertyAnimation* _selectMarkTopAnimation{nullptr};
    QPropertyAnimation* _selectMarkBottomAnimation{nullptr};
    bool _compareItemY(YyNavigationNode* node1, YyNavigationNode* node2);
};

#endif // YyFOOTERDELEGATE_H

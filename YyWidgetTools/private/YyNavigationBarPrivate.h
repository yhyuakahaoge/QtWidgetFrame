#ifndef YyNAVIGATIONBARPRIVATE_H
#define YyNAVIGATIONBARPRIVATE_H

#include "YyDef.h"
#include "YySuggestBox.h"
#include <QMap>
#include <QObject>
class QLayout;
class YyMenu;
class QVBoxLayout;
class QHBoxLayout;
class QLinearGradient;

class YyNavigationBar;
class YyNavigationNode;
class YyNavigationModel;
class YyNavigationView;
class YyInteractiveCard;

class YyBaseListView;
class YyFooterModel;
class YyFooterDelegate;
class YyIconButton;
class YyToolButton;
class YyNavigationBarPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(YyNavigationBar)
    Q_PROPERTY_CREATE_D(bool, IsTransparent)
    // Q_PROPERTY_CREATE_D(bool, IsAllowPageOpenInNewWindow)
    Q_PROPERTY_CREATE_D(int, NavigationBarWidth)
    Q_PROPERTY_CREATE(int, NavigationViewWidth);
    Q_PROPERTY_CREATE(int, UserButtonSpacing);

public:
    explicit YyNavigationBarPrivate(QObject* parent = nullptr);
    ~YyNavigationBarPrivate() override;
    // Q_SLOT void onNavigationOpenNewWindow(QString nodeKey);

    // Q_INVOKABLE void onNavigationRoute(QVariantMap routeData);

    // //核心跳转逻辑
    // void onTreeViewClicked(const QModelIndex& index, bool isLogRoute = true, bool isRouteBack = false);
    // void onFooterViewClicked(const QModelIndex& index, bool isLogRoute = true, bool isRouteBack = false);

protected:
    virtual bool eventFilter(QObject* watched, QEvent* event) override;

private:
    // friend class YyNavigationView;
    // friend class YyNavigationStyle;
    YyThemeType::ThemeMode _themeMode;
    // QList<YySuggestBox::SuggestData> _suggestDataList;
    // QMap<QString, const QMetaObject*> _pageMetaMap;
    // QMap<QString, int> _pageNewWindowCountMap;
    // QMap<YyNavigationNode*, YyMenu*> _compactMenuMap;
    QVBoxLayout* _userCardLayout{nullptr};
    QVBoxLayout* _userButtonLayout{nullptr};

    YyIconButton* _userButton{nullptr};
    // YyNavigationModel* _navigationModel{nullptr};
    // YyNavigationView* _navigationView{nullptr};
    // YyBaseListView* _footerView{nullptr};
    // YyFooterModel* _footerModel{nullptr};
    // YyFooterDelegate* _footerDelegate{nullptr};
    YyInteractiveCard* _userCard{nullptr};
    bool _isShowUserCard{true};

    // QList<YyNavigationNode*> _lastExpandedNodesList;

    YyNavigationType::NavigationDisplayMode _currentDisplayMode{YyNavigationType::NavigationDisplayMode::Maximal};
    // void _initNodeModelIndex(const QModelIndex& parentIndex);
    // void _resetNodeSelected();
    // void _expandSelectedNodeParent();
    // void _expandOrCollapseExpanderNode(YyNavigationNode* node, bool isExpand);

    // void _addStackedPage(QWidget* page, QString pageKey);
    // void _addFooterPage(QWidget* page, QString footKey);

    // void _raiseNavigationBar();
    // void _smoothScrollNavigationView(const QModelIndex& index);

    // void _doComponentAnimation(YyNavigationType::NavigationDisplayMode displayMode, bool isAnimation);
    // void _handleNavigationExpandState(bool isSave);
    // void _resetLayout();

    // void _doNavigationBarWidthAnimation(YyNavigationType::NavigationDisplayMode displayMode, bool isAnimation);
    // void _doNavigationViewWidthAnimation(bool isAnimation);
    // void _doUserButtonAnimation(bool isCompact, bool isAnimation);
};

#endif // YyNAVIGATIONBARPRIVATE_H

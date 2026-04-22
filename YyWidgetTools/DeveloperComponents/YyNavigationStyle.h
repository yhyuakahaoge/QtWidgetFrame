#ifndef YyNAVIGATIONSTYLE_H
#define YyNAVIGATIONSTYLE_H
#include <QModelIndex>
#include <QProxyStyle>

#include "YyDef.h"
class YyNavigationNode;
class YyNavigationView;
class QPropertyAnimation;
class YyNavigationStyle : public QProxyStyle
{
    Q_OBJECT
    Q_PROPERTY_CREATE(qreal, Opacity)
    Q_PROPERTY_CREATE(qreal, Rotate)
    Q_PROPERTY_CREATE(int, ItemHeight)
    Q_PRIVATE_CREATE(YyNavigationView*, NavigationView)
    Q_PROPERTY_CREATE(qreal, LastSelectMarkTop)
    Q_PROPERTY_CREATE(qreal, LastSelectMarkBottom)
    Q_PROPERTY_CREATE(qreal, SelectMarkTop)
    Q_PROPERTY_CREATE(qreal, SelectMarkBottom)
    Q_PRIVATE_CREATE(QModelIndex, PressIndex)
public:
    explicit YyNavigationStyle(QStyle* style = nullptr);
    ~YyNavigationStyle() override;
    void drawPrimitive(PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget = nullptr) const override;
    void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget = nullptr) const override;
    QSize sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& size, const QWidget* widget) const override;

    void navigationNodeStateChange(QVariantMap data);

private:
    YyThemeType::ThemeMode _themeMode;
    bool _isSelectMarkDisplay{true};
    int _leftPadding{11};
    int _iconAreaWidth{40};
    int _textRightSpacing{3};
    int _indicatorIconAreaWidth{34};
    YyNavigationNode* _opacityAnimationTargetNode{nullptr};
    YyNavigationNode* _expandAnimationTargetNode{nullptr};
    YyNavigationNode* _lastSelectedNode{nullptr};
    QPropertyAnimation* _lastSelectMarkTopAnimation{nullptr};
    QPropertyAnimation* _lastSelectMarkBottomAnimation{nullptr};
    QPropertyAnimation* _selectMarkTopAnimation{nullptr};
    QPropertyAnimation* _selectMarkBottomAnimation{nullptr};
    bool _compareItemY(YyNavigationNode* node1, YyNavigationNode* node2);
};

#endif // YyNAVIGATIONSTYLE_H

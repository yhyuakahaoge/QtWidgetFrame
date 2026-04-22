#ifndef YYWINDOW_H
#define YYWINDOW_H

#include <QMainWindow>
#include "YyDef.h"
#include "YyAppBar.h"
class YyWindowPrivate;
class Yy_EXPORT YyWindow : public QMainWindow
{
    Q_OBJECT
    Q_Q_CREATE(YyWindow)
    Q_PROPERTY_CREATE_Q_H(bool, IsStayTop)
    Q_PROPERTY_CREATE_Q_H(bool, IsFixedSize)
    Q_PROPERTY_CREATE_Q_H(bool, IsDefaultClosed)
    Q_PROPERTY_CREATE_Q_H(int, AppBarHeight)
    Q_PROPERTY_CREATE_Q_H(int, ThemeChangeTime)
    //Q_PROPERTY_CREATE_Q_H(bool, IsCentralStackedWidgetTransparent)
    // Q_PROPERTY_CREATE_Q_H(bool, IsAllowPageOpenInNewWindow)
    Q_PROPERTY_CREATE_Q_H(bool, IsNavigationBarEnable)
    Q_PROPERTY_CREATE_Q_H(int, NavigationBarWidth)
    // Q_PROPERTY_CREATE_Q_H(int, CurrentStackIndex)
    Q_PROPERTY_CREATE_Q_H(YyNavigationType::NavigationDisplayMode, NavigationBarDisplayMode)
    // Q_PROPERTY_CREATE_Q_H(YyWindowType::StackSwitchMode, StackSwitchMode)
    Q_PROPERTY_CREATE_Q_H(YyWindowType::PaintMode, WindowPaintMode)
    Q_TAKEOVER_NATIVEEVENT_H
public:
    Q_INVOKABLE explicit YyWindow(QWidget* parent = nullptr); //可动态创建
    virtual ~YyWindow() override;

    void moveToCenter();

    void setCustomWidget(YyAppBarType::CustomArea customArea, QWidget* customWidget, QObject* hitTestObject = nullptr, const QString& hitTestFunctionName = "");
    QWidget* getCustomWidget(YyAppBarType::CustomArea customArea) const;
    void setWindowPixmap(YyThemeType::ThemeMode themeMode, const QPixmap& pixmap);
    QPixmap getWindowPixmap(YyThemeType::ThemeMode themeMode) const;
    void setWindowMoviePath(YyThemeType::ThemeMode themeMode, const QString& moviePath);

    void setUserInfoCardVisible(bool isVisible);
    void setUserInfoCardPixmap(QPixmap pix);
    void setUserInfoCardTitle(QString title);
    void setUserInfoCardSubTitle(QString subTitle);

    void setCentralCustomWidget(QWidget* customWidget);
    QWidget* getCentralCustomWidget() const;

    void setCustomMenu(QMenu* customMenu);
    QMenu* getCustomMenu() const;

    YyNavigationType::NodeResult addExpanderNode(const QString& expanderTitle, QString& expanderKey, YyIconType::IconName awesome = YyIconType::None) const;
    YyNavigationType::NodeResult addExpanderNode(const QString& expanderTitle, QString& expanderKey, const QString& targetExpanderKey, YyIconType::IconName awesome = YyIconType::None) const;
    YyNavigationType::NodeResult addPageNode(const QString& pageTitle, QWidget* page, YyIconType::IconName awesome = YyIconType::None);
    YyNavigationType::NodeResult addPageNode(const QString& pageTitle, QWidget* page, int keyPoints, YyIconType::IconName awesome = YyIconType::None);
    YyNavigationType::NodeResult addPageNode(const QString& pageTitle, QWidget* page, const QString& targetExpanderKey, YyIconType::IconName awesome = YyIconType::None);
    YyNavigationType::NodeResult addPageNode(const QString& pageTitle, QWidget* page, const QString& targetExpanderKey, int keyPoints, YyIconType::IconName awesome = YyIconType::None);
    YyNavigationType::NodeResult addFooterNode(const QString& footerTitle, QString& footerKey, int keyPoints = 0, YyIconType::IconName awesome = YyIconType::None) const;
    YyNavigationType::NodeResult addFooterNode(const QString& footerTitle, QWidget* page, QString& footerKey, int keyPoints = 0, YyIconType::IconName awesome = YyIconType::None);
    YyNavigationType::NodeResult addCategoryNode(const QString& categoryTitle, QString& categoryKey);
    YyNavigationType::NodeResult addCategoryNode(const QString& categoryTitle, QString& categoryKey, const QString& targetExpanderKey);

    void addCentralWidget(QWidget* centralWidget);
    QWidget* getCentralWidget(int index) const;

    bool getNavigationNodeIsExpanded(QString expanderKey) const;
    void expandNavigationNode(QString expanderKey);
    void collapseNavigationNode(QString expanderKey);
    void removeNavigationNode(QString nodeKey) const;
    int getPageOpenInNewWindowCount(QString nodeKey) const;

    void closeWindow();
Q_SIGNALS:
    Q_SIGNAL void userInfoCardClicked();
    Q_SIGNAL void closeButtonClicked();
    Q_SIGNAL void navigationNodeClicked(YyNavigationType::NavigationNodeType nodeType, QString nodeKey);
    Q_SIGNAL void customWidgetChanged();
    Q_SIGNAL void centralCustomWidgetChanged();
    Q_SIGNAL void customMenuChanged();
    Q_SIGNAL void pageOpenInNewWindow(QString nodeKey);

protected:
    virtual bool eventFilter(QObject* watched, QEvent* event) override;
    virtual QMenu* createPopupMenu() override;
    virtual void paintEvent(QPaintEvent* event) override;
};

#endif // YYWINDOW_H

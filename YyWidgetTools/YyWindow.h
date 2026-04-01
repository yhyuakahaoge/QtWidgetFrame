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
    // Q_PROPERTY_CREATE_Q_H(bool, IsNavigationBarEnable)
    // Q_PROPERTY_CREATE_Q_H(int, NavigationBarWidth)
    // Q_PROPERTY_CREATE_Q_H(int, CurrentStackIndex)
    // Q_PROPERTY_CREATE_Q_H(YyNavigationType::NavigationDisplayMode, NavigationBarDisplayMode)
    // Q_PROPERTY_CREATE_Q_H(YyWindowType::StackSwitchMode, StackSwitchMode)
    Q_PROPERTY_CREATE_Q_H(YyWindowType::PaintMode, WindowPaintMode)
    Q_TAKEOVER_NATIVEEVENT_H
public:
    Q_INVOKABLE explicit YyWindow(QWidget* parent = nullptr); //可动态创建
    virtual ~YyWindow() override;

    void moveToCenter();
    void setCustomWidget(YyAppBarType::CustomArea customArea, QWidget* customWidget, QObject* hitTestObject = nullptr, const QString& hitTestFunctionName = "");
    QWidget* getCustomWidget(YyAppBarType::CustomArea customArea) const;

Q_SIGNALS:
    Q_SIGNAL void userInfoCardClicked();
    Q_SIGNAL void closeButtonClicked();
    Q_SIGNAL void navigationNodeClicked(YyNavigationType::NavigationNodeType nodeType, QString nodeKey);
    Q_SIGNAL void customWidgetChanged();
    Q_SIGNAL void centralCustomWidgetChanged();
    Q_SIGNAL void customMenuChanged();
    Q_SIGNAL void pageOpenInNewWindow(QString nodeKey);
};

#endif // YYWINDOW_H

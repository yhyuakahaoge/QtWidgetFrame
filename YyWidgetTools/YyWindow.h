#ifndef YYWINDOW_H
#define YYWINDOW_H

#include <QMainWindow>
#include "YyDef.h"

class YyWindowPrivate;
class Yy_EXPORT YyWindow : public QMainWindow
{
    Q_OBJECT
    Q_Q_CREATE(YyWindow)
    Q_PROPERTY_CREATE_Q_H(bool, IsStayTop)
public:
    Q_INVOKABLE explicit YyWindow(QWidget* parent = nullptr); //可动态创建
    virtual ~YyWindow() override;

    void moveToCenter();
    void setCustomWidget(ElaAppBarType::CustomArea customArea, QWidget* customWidget, QObject* hitTestObject = nullptr, const QString& hitTestFunctionName = "");
    QWidget* getCustomWidget(ElaAppBarType::CustomArea customArea) const;
};

#endif // YYWINDOW_H

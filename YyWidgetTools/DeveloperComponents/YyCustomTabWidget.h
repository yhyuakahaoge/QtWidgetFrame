#ifndef YyCUSTOMTABWIDGET_H
#define YyCUSTOMTABWIDGET_H

#include "YyCustomWidget.h"

class YyTabBar;
class YyTabWidget;
class YyCustomTabWidget : public YyCustomWidget
{
    Q_OBJECT
    Q_PROPERTY_CREATE(bool, IsFinished)
public:
    explicit YyCustomTabWidget(QWidget* parent = nullptr);
    virtual ~YyCustomTabWidget() override;
    void addTab(QWidget* widget, QIcon tabIcon, const QString& tabTitle);
    YyTabBar* getCustomTabBar() const;
    YyTabWidget* getCustomTabWidget() const;

    Q_INVOKABLE bool processHitTest();

private:
    bool _isAllowLeave{false};
    YyTabBar* _customTabBar{nullptr};
    YyTabWidget* _customTabWidget{nullptr};
};

#endif // YyCUSTOMTABWIDGET_H

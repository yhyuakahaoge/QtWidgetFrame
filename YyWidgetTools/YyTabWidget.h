#ifndef YyTABWIDGET_H
#define YyTABWIDGET_H

#include <QTabWidget>

#include "YyProperty.h"

class YyTabWidgetPrivate;
class Yy_EXPORT YyTabWidget : public QTabWidget
{
    Q_OBJECT
    Q_Q_CREATE(YyTabWidget)
    Q_PROPERTY_CREATE_Q_H(bool, IsTabTransparent);
    Q_PROPERTY_CREATE_Q_H(bool, IsContainerAcceptDrops);
    Q_PROPERTY_CREATE_Q_H(QSize, TabSize)
public:
    explicit YyTabWidget(QWidget* parent = nullptr);
    ~YyTabWidget() override;
    void setTabPosition(TabPosition position);

protected:
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void dragEnterEvent(QDragEnterEvent* event) override;
    virtual void dropEvent(QDropEvent* event) override;
    virtual void tabInserted(int index) override;

private:
    friend class YyCustomTabWidget;
};

#endif // YyTABWIDGET_H

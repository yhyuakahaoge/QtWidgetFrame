#ifndef YyTABWIDGETPRIVATE_H
#define YyTABWIDGETPRIVATE_H

#include "YyProperty.h"
#include "YySingleton.h"
#include <QDrag>
#include <QObject>
#include <QPixmap>
class YyDragMonitor : public QObject
{
    Q_OBJECT
    Q_PRIVATE_CREATE(bool, IsInDrag)
    Q_SINGLETON_CREATE(YyDragMonitor)
private:
    explicit YyDragMonitor(QObject* parent = nullptr);
    ~YyDragMonitor() override;
};

class YyTabWidget;
class YyTabBar;
class YyTabWidgetPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(YyTabWidget)
    Q_PROPERTY_CREATE_D(bool, IsTabTransparent)
    Q_PROPERTY_CREATE_D(bool, IsContainerAcceptDrops);
    Q_PROPERTY_CREATE_D(QSize, TabSize)
public:
    explicit YyTabWidgetPrivate(QObject* parent = nullptr);
    ~YyTabWidgetPrivate() override;
    Q_SLOT void onTabDragCreate(QMimeData* mimeData);
    Q_SLOT void onTabDragEnter(QMimeData* mimeData);
    Q_SLOT void onTabDragLeave(QMimeData* mimeData);
    Q_SLOT void onTabDragDrop(QMimeData* mimeData);
    Q_SLOT void onTabCloseRequested(int index);

private:
    friend class YyCustomTabWidget;
    YyTabBar* _tabBar{nullptr};
    YyTabBar* _customTabBar{nullptr};
    QList<QWidget*> _allTabWidgetList;
    void _clearAllTabWidgetList();
};

#endif // YyTABWIDGETPRIVATE_H

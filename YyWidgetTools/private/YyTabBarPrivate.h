#ifndef YyTABBARPRIVATE_H
#define YyTABBARPRIVATE_H

#include "YyProperty.h"
#include <QMimeData>
#include <QObject>
#include <QPixmap>
class YyTabBar;
class YyTabBarStyle;
class QTabBarPrivate;
class YyTabBarPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(YyTabBar)
public:
    explicit YyTabBarPrivate(QObject* parent = nullptr);
    ~YyTabBarPrivate() override;

private:
    // 拖放数据容器
    QMimeData* _mimeData{nullptr};
    YyTabBarStyle* _style{nullptr};
    QTabBarPrivate* _tabBarPrivate{nullptr};
};

#endif // YyTABBARPRIVATE_H

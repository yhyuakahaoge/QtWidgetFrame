#ifndef ELAWINDOWPRIVATE_H
#define ELAWINDOWPRIVATE_H

#include "YyDef.h"


class QLabel;
class QScreen;
class QHBoxLayout;
class QVBoxLayout;
class YyAppBar;
class YyAppBarPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(YyAppBar)
    Q_PROPERTY_CREATE_D(bool, IsStayTop)
    Q_PROPERTY_CREATE_D(bool, IsFixedSize)
    Q_PROPERTY_CREATE_D(bool, IsDefaultClosed)
    Q_PROPERTY_CREATE_D(bool, IsOnlyAllowMinAndClose)
    Q_PROPERTY_CREATE_D(int, AppBarHeight)
public:
    explicit YyAppBarPrivate(QObject* parent = nullptr);
    virtual ~YyAppBarPrivate() override;
};

#endif // ELAWINDOWPRIVATE_H

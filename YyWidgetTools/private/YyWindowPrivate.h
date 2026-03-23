#ifndef ELAWINDOWPRIVATE_H
#define ELAWINDOWPRIVATE_H

#include "YyDef.h"
#include <QLinearGradient>
#include <QMap>
#include <QMovie>
#include <QObject>

class YyWindow;
class YyAppBar;
class YyWindowPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(YyWindow)

public:
    explicit YyWindowPrivate(QObject* parent = nullptr);
    virtual ~YyWindowPrivate() override;

private:
    YyAppBar* _appBar{nullptr};
};

#endif // ELAWINDOWPRIVATE_H

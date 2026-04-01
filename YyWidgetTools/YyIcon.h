#ifndef YyICON_H
#define YyICON_H
#include <QIcon>

#include "YyDef.h"
#include "YyProperty.h"
#include "YySingleton.h"
class Yy_EXPORT YyIcon
{
    Q_SINGLETON_CREATE_H(YyIcon)
private:
    explicit YyIcon();
    ~YyIcon();

public:
    QIcon getYyIcon(YyIconType::IconName awesome);
    QIcon getYyIcon(YyIconType::IconName awesome, QColor iconColor);
    QIcon getYyIcon(YyIconType::IconName awesome, int pixelSize);
    QIcon getYyIcon(YyIconType::IconName awesome, int pixelSize, QColor iconColor);
    QIcon getYyIcon(YyIconType::IconName awesome, int pixelSize, int fixedWidth, int fixedHeight);
    QIcon getYyIcon(YyIconType::IconName awesome, int pixelSize, int fixedWidth, int fixedHeight, QColor iconColor);
};

#endif // YyICON_H

#ifndef YyINTERACTIVECARDPRIVATE_H
#define YyINTERACTIVECARDPRIVATE_H

#include <QImage>
#include <QObject>
#include <QPixmap>
#include <QSize>

#include "YyDef.h"
class YyInteractiveCard;
class YyInteractiveCardPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(YyInteractiveCard)
    Q_PROPERTY_CREATE_D(int, BorderRadius)
    Q_PROPERTY_CREATE_D(QString, Title);
    Q_PROPERTY_CREATE_D(QString, SubTitle);
    Q_PROPERTY_CREATE_D(int, TitlePixelSize);
    Q_PROPERTY_CREATE_D(int, SubTitlePixelSize);
    Q_PROPERTY_CREATE_D(int, TitleSpacing);
    Q_PROPERTY_CREATE_D(QPixmap, CardPixmap);
    Q_PROPERTY_CREATE_D(QSize, CardPixmapSize);
    Q_PROPERTY_CREATE_D(int, CardPixmapBorderRadius)
    Q_PROPERTY_CREATE_D(YyCardPixType::PixMode, CardPixMode);

public:
    explicit YyInteractiveCardPrivate(QObject* parent = nullptr);
    ~YyInteractiveCardPrivate();

private:
    YyThemeType::ThemeMode _themeMode;
};

#endif // YyINTERACTIVECARDPRIVATE_H

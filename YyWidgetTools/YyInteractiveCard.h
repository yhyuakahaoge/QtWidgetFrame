#ifndef YyINTERACTIVECARD_H
#define YyINTERACTIVECARD_H

#include <QPixmap>
#include <QPushButton>

#include "YyDef.h"
#include "YyProperty.h"

class YyInteractiveCardPrivate;
class Yy_EXPORT YyInteractiveCard : public QPushButton
{
    Q_OBJECT
    Q_Q_CREATE(YyInteractiveCard)
    Q_PROPERTY_CREATE_Q_H(int, BorderRadius)
    Q_PROPERTY_CREATE_Q_H(QString, Title);
    Q_PROPERTY_CREATE_Q_H(QString, SubTitle);
    Q_PROPERTY_CREATE_Q_H(int, TitlePixelSize);
    Q_PROPERTY_CREATE_Q_H(int, SubTitlePixelSize);
    Q_PROPERTY_CREATE_Q_H(int, TitleSpacing);
    Q_PROPERTY_CREATE_Q_H(QPixmap, CardPixmap);
    Q_PROPERTY_CREATE_Q_H(QSize, CardPixmapSize);
    Q_PROPERTY_CREATE_Q_H(int, CardPixmapBorderRadius)
    Q_PROPERTY_CREATE_Q_H(YyCardPixType::PixMode, CardPixMode);

public:
    explicit YyInteractiveCard(QWidget* parent = nullptr);
    ~YyInteractiveCard();
    void setCardPixmapSize(int width, int height);

protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif // YyINTERACTIVECARD_H

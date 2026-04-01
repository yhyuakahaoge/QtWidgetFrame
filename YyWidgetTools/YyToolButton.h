#ifndef YyTOOLBUTTON_H
#define YyTOOLBUTTON_H

#include <QToolButton>

#include "YyDef.h"
class YyMenu;
class YyToolButtonPrivate;
class Yy_EXPORT YyToolButton : public QToolButton
{
    Q_OBJECT
    Q_Q_CREATE(YyToolButton)
    Q_PROPERTY_CREATE_Q_H(int, BorderRadius);
    Q_PROPERTY_CREATE_Q_H(bool, IsSelected);

public:
    explicit YyToolButton(QWidget* parent = nullptr);
    ~YyToolButton() override;

    void setIsTransparent(bool isTransparent);
    bool getIsTransparent() const;

    void setMenu(YyMenu* menu);
    void setYyIcon(YyIconType::IconName icon);
    void setYyIcon(YyIconType::IconName icon, int rotate);

protected:
    virtual bool eventFilter(QObject* watched, QEvent* event) override;
};

#endif // YyTOOLBUTTON_H

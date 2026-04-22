#ifndef YyTOOLTIPPRIVATE_H
#define YyTOOLTIPPRIVATE_H

#include <QObject>

#include "YyDef.h"
class YyToolTip;
class QVBoxLayout;
class YyText;
class YyToolTipPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(YyToolTip)
    Q_PROPERTY_CREATE_D(int, BorderRadius)
    Q_PROPERTY_CREATE_D(int, DisplayMsec)
    Q_PROPERTY_CREATE_D(int, ShowDelayMsec)
    Q_PROPERTY_CREATE_D(int, HideDelayMsec)
    Q_PROPERTY_CREATE_D(QString, ToolTip)
    Q_PROPERTY_CREATE_D(QWidget*, CustomWidget)
    Q_PROPERTY_CREATE(qreal, Opacity)

public:
    explicit YyToolTipPrivate(QObject* parent = nullptr);
    ~YyToolTipPrivate() override;

protected:
    virtual bool eventFilter(QObject* watched, QEvent* event) override;

private:
    YyText* _toolTipText{nullptr};
    QVBoxLayout* _mainLayout{nullptr};
    YyThemeType::ThemeMode _themeMode;
    int _shadowBorderWidth{6};
    void _doShowAnimation();
    void _updatePos();
};

#endif // YyTOOLTIPPRIVATE_H

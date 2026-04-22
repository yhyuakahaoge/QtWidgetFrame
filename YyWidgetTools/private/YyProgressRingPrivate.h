#ifndef YyFRAMEWORK_YyWIDGETTOOLS_PRIVATE_YyPROGRESSRINGPRIVATE_H_
#define YyFRAMEWORK_YyWIDGETTOOLS_PRIVATE_YyPROGRESSRINGPRIVATE_H_

#include <QObject>

#include "YyDef.h"
class YyProgressRing;
class QPropertyAnimation;
class YyProgressRingPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(YyProgressRing);
    Q_PROPERTY_CREATE_D(bool, IsBusying)
    Q_PROPERTY_CREATE_D(bool, IsTransparent)
    Q_PROPERTY_CREATE_D(bool, IsDisplayValue)
    Q_PROPERTY_CREATE_D(YyProgressRingType::ValueDisplayMode, ValueDisplayMode)
    Q_PROPERTY_CREATE_D(int, BusyingWidth)
    Q_PROPERTY_CREATE_D(int, BusyingDurationTime)
    Q_PROPERTY_CREATE_D(int, Minimum)
    Q_PROPERTY_CREATE_D(int, Maximum)
    Q_PROPERTY_CREATE_D(int, Value)
    Q_PROPERTY_CREATE_D(int, ValuePixelSize)
    Q_PROPERTY_CREATE(int, BusyIndex)
    Q_PROPERTY_CREATE(int, BusyStartDeg)
    Q_PROPERTY_CREATE(int, BusyContentDeg)
public:
    explicit YyProgressRingPrivate(QObject* parent = nullptr);
    ~YyProgressRingPrivate() override;

private:
    YyThemeType::ThemeMode _themeMode;
    QPropertyAnimation* _busyStartDegAnimation{nullptr};
    QPropertyAnimation* _busyContentDegAnimation{nullptr};
};

#endif //YyFRAMEWORK_YyWIDGETTOOLS_PRIVATE_YyPROGRESSRINGPRIVATE_H_

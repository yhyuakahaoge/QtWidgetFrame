#ifndef YyFRAMEWORK_YyWIDGETTOOLS_INCLUDE_YyPROGRESSRING_H_
#define YyFRAMEWORK_YyWIDGETTOOLS_INCLUDE_YyPROGRESSRING_H_

#include "YyDef.h"

#include <QWidget>

class YyProgressRingPrivate;
class Yy_EXPORT YyProgressRing : public QWidget
{
    Q_OBJECT
    Q_Q_CREATE(YyProgressRing);
    Q_PROPERTY_CREATE_Q_H(bool, IsBusying)
    Q_PROPERTY_CREATE_Q_H(bool, IsTransparent)
    Q_PROPERTY_CREATE_Q_H(bool, IsDisplayValue)
    Q_PROPERTY_CREATE_Q_H(YyProgressRingType::ValueDisplayMode, ValueDisplayMode)
    Q_PROPERTY_CREATE_Q_H(int, BusyingWidth)
    Q_PROPERTY_CREATE_Q_H(int, BusyingDurationTime)
    Q_PROPERTY_CREATE_Q_H(int, Minimum)
    Q_PROPERTY_CREATE_Q_H(int, Maximum)
    Q_PROPERTY_CREATE_Q_H(int, Value)
    Q_PROPERTY_CREATE_Q_H(int, ValuePixelSize)
public:
    explicit YyProgressRing(QWidget* parent = nullptr);
    ~YyProgressRing() override;

    void setRange(int min, int max);

Q_SIGNALS:
    Q_SIGNAL void rangeChanged(int min, int max);

protected:
    virtual void paintEvent(QPaintEvent* event) override;
};

#endif //YyFRAMEWORK_YyWIDGETTOOLS_INCLUDE_YyPROGRESSRING_H_

#include "YyProgressRing.h"

#include "YyProgressRingPrivate.h"
#include "YyTheme.h"
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QtMath>
Q_PROPERTY_CREATE_Q_CPP(YyProgressRing, bool, IsTransparent)
Q_PROPERTY_CREATE_Q_CPP(YyProgressRing, bool, IsDisplayValue)
Q_PROPERTY_CREATE_Q_CPP(YyProgressRing, YyProgressRingType::ValueDisplayMode, ValueDisplayMode)
Q_PROPERTY_CREATE_Q_CPP(YyProgressRing, int, ValuePixelSize)
YyProgressRing::YyProgressRing(QWidget* parent)
    : QWidget(parent), d_ptr(new YyProgressRingPrivate())
{
    Q_D(YyProgressRing);
    d->q_ptr = this;
    d->_pIsDisplayValue = true;
    d->_pValuePixelSize = 17;
    d->_pValueDisplayMode = YyProgressRingType::ValueDisplayMode::Actual;
    d->_pMinimum = 0;
    d->_pMaximum = 100;
    d->_pValue = 0;
    d->_pBusyIndex = 0xe100;
    d->_pBusyingDurationTime = 1000;
    d->_pBusyingWidth = 6;
    d->_pBusyStartDeg = 0;
    d->_pBusyContentDeg = 0;
    d->_pIsBusying = false;
    d->_pIsTransparent = false;
    setFixedSize(70, 70);
    setObjectName("YyProgressRing");
    setStyleSheet("#YyProgressRing{background-color:transparent;}");

    d->_busyStartDegAnimation = new QPropertyAnimation(d, "pBusyStartDeg");
    connect(d->_busyStartDegAnimation, &QPropertyAnimation::valueChanged, this, [=]() {
        update();
    });
    d->_busyStartDegAnimation->setEasingCurve(QEasingCurve::Linear);
    d->_busyStartDegAnimation->setDuration(1000);
    d->_busyStartDegAnimation->setStartValue(0);
    d->_busyStartDegAnimation->setEndValue(360);
    d->_busyStartDegAnimation->setLoopCount(-1);

    d->_busyContentDegAnimation = new QPropertyAnimation(d, "pBusyContentDeg");
    d->_busyContentDegAnimation->setEasingCurve(QEasingCurve::Linear);
    d->_busyContentDegAnimation->setDuration(1800);
    d->_busyContentDegAnimation->setStartValue(10);
    d->_busyContentDegAnimation->setKeyValueAt(0.5, 140);
    d->_busyContentDegAnimation->setEndValue(10);
    d->_busyContentDegAnimation->setLoopCount(-1);

    d->_themeMode = eTheme->getThemeMode();
    connect(eTheme, &YyTheme::themeModeChanged, this, [=](YyThemeType::ThemeMode themeMode) {
        d->_themeMode = themeMode;
        update();
    });
}

YyProgressRing::~YyProgressRing()
{
}

void YyProgressRing::setIsBusying(bool isBusying)
{
    Q_D(YyProgressRing);
    d->_pIsBusying = isBusying;
    if (isBusying)
    {
        d->_busyStartDegAnimation->start();
        d->_busyContentDegAnimation->start();
    }
    else
    {
        d->_busyStartDegAnimation->stop();
        d->_busyContentDegAnimation->stop();
    }
    update();
    Q_EMIT pIsBusyingChanged();
}

bool YyProgressRing::getIsBusying() const
{
    Q_D(const YyProgressRing);
    return d->_pIsBusying;
}

void YyProgressRing::setBusyingWidth(int width)
{
    Q_D(YyProgressRing);
    d->_pBusyingWidth = width;
    update();
    Q_EMIT pBusyingWidthChanged();
}

int YyProgressRing::getBusyingWidth() const
{
    Q_D(const YyProgressRing);
    return d->_pBusyingWidth;
}

void YyProgressRing::setBusyingDurationTime(int busyingDurationTime)
{
    Q_D(YyProgressRing);
    d->_pBusyingDurationTime = busyingDurationTime;
    d->_busyStartDegAnimation->setDuration(d->_pBusyingDurationTime);
    Q_EMIT pBusyingDurationTimeChanged();
}

int YyProgressRing::getBusyingDurationTime() const
{
    Q_D(const YyProgressRing);
    return d->_pBusyingDurationTime;
}

void YyProgressRing::setMinimum(int minimum)
{
    Q_D(YyProgressRing);
    d->_pMinimum = minimum;
    update();
    Q_EMIT pMinimumChanged();
    Q_EMIT rangeChanged(d->_pMinimum, d->_pMaximum);
}

int YyProgressRing::getMinimum() const
{
    Q_D(const YyProgressRing);
    return d->_pMinimum;
}

void YyProgressRing::setMaximum(int maximum)
{
    Q_D(YyProgressRing);
    d->_pMaximum = maximum;
    update();
    Q_EMIT pMaximumChanged();
    Q_EMIT rangeChanged(d->_pMinimum, d->_pMaximum);
}

int YyProgressRing::getMaximum() const
{
    Q_D(const YyProgressRing);
    return d->_pMaximum;
}

void YyProgressRing::setValue(int value)
{
    Q_D(YyProgressRing);
    if (value < d->_pMinimum || value > d->_pMaximum)
    {
        return;
    }
    d->_pValue = value;
    update();
    Q_EMIT pValueChanged();
}

int YyProgressRing::getValue() const
{
    Q_D(const YyProgressRing);
    return d->_pValue;
}

void YyProgressRing::setRange(int min, int max)
{
    Q_D(YyProgressRing);
    if (min < 0 || max < 0 || min > max)
    {
        return;
    }
    d->_pMinimum = min;
    d->_pMaximum = max;
    update();
    Q_EMIT pMinimumChanged();
    Q_EMIT pMaximumChanged();
    Q_EMIT rangeChanged(min, max);
}

void YyProgressRing::paintEvent(QPaintEvent* event)
{
    Q_D(YyProgressRing);
    QPainter painter(this);
    painter.save();
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    // 文字绘制
    if (d->_pIsDisplayValue && !d->_pIsBusying)
    {
        painter.setPen(YyThemeColor(d->_themeMode, BasicText));
        QString valueText;
        if (d->_pValueDisplayMode == YyProgressRingType::ValueDisplayMode::Actual)
        {
            valueText = QString::number(d->_pValue);
        }
        else
        {
            valueText = QString::number(d->_pValue / (qreal)(d->_pMaximum - d->_pMinimum) * 100) + "%";
        }
        painter.drawText(rect(), Qt::AlignCenter | Qt::TextSingleLine, valueText);
    }
    // Ring绘制
    QRect ringRect = rect().adjusted(1, 1, -1, -1);
    // 遮罩
    QPainterPath basePath;
    basePath.addEllipse(ringRect);
    QPainterPath maskPath;
    maskPath.addEllipse(ringRect.adjusted(d->_pBusyingWidth, d->_pBusyingWidth, -d->_pBusyingWidth, -d->_pBusyingWidth));
    painter.setClipPath(basePath.subtracted(maskPath));
    painter.setPen(Qt::NoPen);
    // 底色
    if (!d->_pIsTransparent)
    {
        painter.setBrush(YyThemeColor(d->_themeMode, BasicBaseDeep));
        painter.drawEllipse(ringRect);
    }
    // 环
    painter.setBrush(YyThemeColor(d->_themeMode, PrimaryNormal));
    if (d->_pIsBusying)
    {
        painter.drawPie(ringRect, -d->_pBusyStartDeg * 16, d->_pBusyContentDeg * 16);
    }
    else
    {
        qreal valueDeg = d->_pValue / (qreal)(d->_pMaximum - d->_pMinimum) * 360;
        painter.drawPie(ringRect, 90 * 16, -valueDeg * 16);
    }
    painter.restore();
}

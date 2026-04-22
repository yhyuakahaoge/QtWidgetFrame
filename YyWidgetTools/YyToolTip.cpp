#include "YyToolTip.h"

#include <QPainter>
#include <QVBoxLayout>

#include "YyText.h"
#include "YyTheme.h"
#include "YyToolTipPrivate.h"
Q_PROPERTY_CREATE_Q_CPP(YyToolTip, int, BorderRadius)
Q_PROPERTY_CREATE_Q_CPP(YyToolTip, int, DisplayMsec)
Q_PROPERTY_CREATE_Q_CPP(YyToolTip, int, ShowDelayMsec)
Q_PROPERTY_CREATE_Q_CPP(YyToolTip, int, HideDelayMsec)
YyToolTip::YyToolTip(QWidget* parent)
    : QWidget{parent}, d_ptr(new YyToolTipPrivate())
{
    Q_D(YyToolTip);
    d->q_ptr = this;
    d->_pBorderRadius = 5;
    d->_pDisplayMsec = -1;
    d->_pShowDelayMsec = 0;
    d->_pHideDelayMsec = 0;
    d->_pCustomWidget = nullptr;
    setObjectName("YyToolTip");
    if (parent)
    {
        parent->installEventFilter(d);
    }
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);

    d->_toolTipText = new YyText(this);
    d->_toolTipText->setWordWrap(false);
    d->_toolTipText->setTextPixelSize(17);
    d->_mainLayout = new QVBoxLayout(this);
    d->_mainLayout->setContentsMargins(d->_shadowBorderWidth * 2, d->_shadowBorderWidth * 2, d->_shadowBorderWidth * 2, d->_shadowBorderWidth * 2);
    d->_mainLayout->addWidget(d->_toolTipText);

    d->_themeMode = eTheme->getThemeMode();
    connect(eTheme, &YyTheme::themeModeChanged, this, [=](YyThemeType::ThemeMode themeMode) {
        d->_themeMode = themeMode;
        update();
    });
    hide();
}

YyToolTip::~YyToolTip()
{
}

void YyToolTip::setToolTip(QString toolTip)
{
    Q_D(YyToolTip);
    // 计算这段文字在当前字体下实际占多少像素宽度
    resize(fontMetrics().horizontalAdvance(toolTip), height());
    d->_toolTipText->setText(toolTip);
    Q_EMIT pToolTipChanged();
}

QString YyToolTip::getToolTip() const
{
    Q_D(const YyToolTip);
    return d->_toolTipText->text();
}

void YyToolTip::setCustomWidget(QWidget* customWidget)
{
    Q_D(YyToolTip);
    if (!customWidget || customWidget == this)
    {
        return;
    }
    if (d->_pCustomWidget)
    {
        d->_mainLayout->removeWidget(d->_pCustomWidget);
        d->_pCustomWidget->deleteLater();
    }
    d->_toolTipText->hide();
    d->_mainLayout->addWidget(customWidget);
    d->_pCustomWidget = customWidget;
    Q_EMIT pCustomWidgetChanged();
}

QWidget* YyToolTip::getCustomWidget() const
{
    Q_D(const YyToolTip);
    return d->_pCustomWidget;
}

void YyToolTip::updatePos()
{
    Q_D(YyToolTip);
    d->_updatePos();
}

void YyToolTip::paintEvent(QPaintEvent* event)
{
    Q_D(YyToolTip);
    QPainter painter(this);
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);
    //阴影
    eTheme->drawEffectShadow(&painter, rect(), d->_shadowBorderWidth, d->_pBorderRadius);
    QRect foregroundRect = rect();
    foregroundRect.adjust(d->_shadowBorderWidth, d->_shadowBorderWidth, -d->_shadowBorderWidth, -d->_shadowBorderWidth);
    painter.setPen(YyThemeColor(d->_themeMode, PopupBorder));
    painter.setBrush(YyThemeColor(d->_themeMode, PopupBase));
    painter.drawRoundedRect(foregroundRect, d->_pBorderRadius, d->_pBorderRadius);
    painter.restore();
}

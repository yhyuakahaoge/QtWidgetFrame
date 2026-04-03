#include "YyThemeAnimationWidget.h"

#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
YyThemeAnimationWidget::YyThemeAnimationWidget(QWidget* parent)
    : QWidget{parent}
{
    _pEndRadius = 0.01;
}

YyThemeAnimationWidget::~YyThemeAnimationWidget()
{
}

void YyThemeAnimationWidget::startAnimation(int msec)
{
    QPropertyAnimation* themeChangeAnimation = new QPropertyAnimation(this, "pRadius");
    themeChangeAnimation->setDuration(msec);
    themeChangeAnimation->setEasingCurve(QEasingCurve::InOutSine);
    connect(themeChangeAnimation, &QPropertyAnimation::finished, this, [=]() {
        Q_EMIT animationFinished();
        this->deleteLater();
    });
    connect(themeChangeAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
        update();
    });
    themeChangeAnimation->setStartValue(0);
    themeChangeAnimation->setEndValue(_pEndRadius);
    themeChangeAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    show();
}

void YyThemeAnimationWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.save();
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    // 无边线
    painter.setPen(Qt::NoPen);

    // 合成图片

    // 创建一个与原图像一样大的透明图像
    QImage animationImage(_pOldWindowBackground.size(), QImage::Format_ARGB32);
    animationImage.fill(Qt::transparent);

    // 专门画在此图像上的画笔
    QPainter animationImagePainter(&animationImage);
    animationImagePainter.setRenderHints(QPainter::Antialiasing);
    animationImagePainter.drawImage(_pOldWindowBackground.rect(), _pOldWindowBackground);
    // 设置混合模式
    animationImagePainter.setCompositionMode(QPainter::CompositionMode::CompositionMode_SourceOut);
    qreal devicePixelRatioF = _pOldWindowBackground.devicePixelRatioF();
    QPainterPath clipPath;
    clipPath.moveTo(_pCenter.x() * devicePixelRatioF, _pCenter.y() * devicePixelRatioF);
    clipPath.addEllipse(QPointF(_pCenter.x() * devicePixelRatioF, _pCenter.y() * devicePixelRatioF), _pRadius * devicePixelRatioF, _pRadius * devicePixelRatioF);
    animationImagePainter.setClipPath(clipPath);
    animationImagePainter.drawImage(animationImage.rect(), animationImage);
    animationImagePainter.end();

    painter.drawImage(rect(), animationImage);
    painter.restore();
}

#include "YyCentralStackedWidget.h"

#include "YyTheme.h"
#include <QApplication>
#include <QDebug>
#include <QGraphicsBlurEffect>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QTimer>
#include <cmath>
YyCentralStackedWidget::YyCentralStackedWidget(QWidget* parent)
    : QWidget(parent)
{
    _pPopupAnimationYOffset = 0;
    _pScaleAnimationRatio = 1;
    _pScaleAnimationPixOpacity = 1;
    _pFlipAnimationRatio = 1;
    _pBlurAnimationRadius = 0;

    setObjectName("YyCentralStackedWidget");
    setStyleSheet("#YyCentralStackedWidget{background-color:transparent;}");

    _containerStackedWidget = new QStackedWidget(this);
    _containerStackedWidget->setObjectName("YyCentralStackedWidget");
    _containerStackedWidget->setStyleSheet("#YyCentralStackedWidget{background-color:transparent;}");

    _blurEffect = new QGraphicsBlurEffect(_containerStackedWidget);
    _blurEffect->setBlurHints(QGraphicsBlurEffect::BlurHint::QualityHint);
    _blurEffect->setBlurRadius(0);
    _blurEffect->setEnabled(false);
    _containerStackedWidget->setGraphicsEffect(_blurEffect);

    _mainLayout = new QVBoxLayout(this);
    _mainLayout->setSpacing(0);
    _mainLayout->setContentsMargins(0, 0, 0, 0);
    _mainLayout->addWidget(_containerStackedWidget);

    _themeMode = eTheme->getThemeMode();
    connect(eTheme, &YyTheme::themeModeChanged, this, &YyCentralStackedWidget::onThemeModeChanged);
}

YyCentralStackedWidget::~YyCentralStackedWidget()
{
}

QStackedWidget* YyCentralStackedWidget::getContainerStackedWidget() const
{
    return _containerStackedWidget;
}

void YyCentralStackedWidget::setCustomWidget(QWidget* widget)
{
    if (!widget)
    {
        return;
    }
    if (_customWidget)
    {
        _mainLayout->removeWidget(_customWidget);
    }
    _mainLayout->insertWidget(0, widget);
    _customWidget = widget;
}

QWidget* YyCentralStackedWidget::getCustomWidget() const
{
    return this->_customWidget;
}

void YyCentralStackedWidget::onThemeModeChanged(YyThemeType::ThemeMode themeMode)
{
    _themeMode = themeMode;
}

void YyCentralStackedWidget::setIsTransparent(bool isTransparent)
{
    this->_isTransparent = isTransparent;
    update();
}

bool YyCentralStackedWidget::getIsTransparent() const
{
    return _isTransparent;
}

void YyCentralStackedWidget::setIsHasRadius(bool isHasRadius)
{
    this->_isHasRadius = isHasRadius;
    update();
}

void YyCentralStackedWidget::doWindowStackSwitch(YyWindowType::StackSwitchMode stackSwitchMode, int nodeIndex, bool isRouteBack)
{
    _stackSwitchMode = stackSwitchMode;
    switch (stackSwitchMode)
    {
    case YyWindowType::None:
    {
        _containerStackedWidget->setCurrentIndex(nodeIndex);
        break;
    }
    case YyWindowType::Popup:
    {
        QTimer::singleShot(180, this, [=]() {
            QWidget* targetWidget = _containerStackedWidget->widget(nodeIndex);
            _containerStackedWidget->setCurrentIndex(nodeIndex);
            _getTargetStackPix();
            targetWidget->setVisible(false);
            QPropertyAnimation* popupAnimation = new QPropertyAnimation(this, "pPopupAnimationYOffset");
            connect(popupAnimation, &QPropertyAnimation::valueChanged, this, [=]() {
                update();
            });
            connect(popupAnimation, &QPropertyAnimation::finished, this, [=]() {
                _targetStackPix = QPixmap();
                targetWidget->setVisible(true);
            });
            popupAnimation->setEasingCurve(QEasingCurve::OutCubic);
            popupAnimation->setDuration(300);
            int targetWidgetY = _containerStackedWidget->mapToParent(QPoint(0, 0)).y();
            popupAnimation->setEndValue(targetWidgetY);
            targetWidgetY += 80;
            popupAnimation->setStartValue(targetWidgetY);
            popupAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        });
        break;
    }
    case YyWindowType::Scale:
    {
        QWidget* targetWidget = _containerStackedWidget->widget(nodeIndex);
        _getCurrentStackPix();
        _containerStackedWidget->setCurrentIndex(nodeIndex);
        _getTargetStackPix();
        targetWidget->setVisible(false);
        _isDrawNewPix = false;
        QPropertyAnimation* currentPixZoomAnimation = new QPropertyAnimation(this, "pScaleAnimationRatio");
        connect(currentPixZoomAnimation, &QPropertyAnimation::valueChanged, this, [=]() {
            update();
        });
        connect(currentPixZoomAnimation, &QPropertyAnimation::finished, this, [=]() {
            _isDrawNewPix = true;
            QPropertyAnimation* targetPixZoomAnimation = new QPropertyAnimation(this, "pScaleAnimationRatio");
            connect(targetPixZoomAnimation, &QPropertyAnimation::valueChanged, this, [=]() {
                update();
            });
            connect(targetPixZoomAnimation, &QPropertyAnimation::finished, this, [=]() {
                _targetStackPix = QPixmap();
                _currentStackPix = QPixmap();
                targetWidget->setVisible(true);
            });
            if (isRouteBack)
            {
                targetPixZoomAnimation->setStartValue(1.5);
                targetPixZoomAnimation->setEndValue(1);
            }
            else
            {
                // 放大
                targetPixZoomAnimation->setStartValue(0.85);
                targetPixZoomAnimation->setEndValue(1);
            }
            targetPixZoomAnimation->setDuration(300);
            targetPixZoomAnimation->setEasingCurve(QEasingCurve::OutCubic);
            targetPixZoomAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        });
        if (isRouteBack)
        {
            // 缩小
            currentPixZoomAnimation->setStartValue(1);
            currentPixZoomAnimation->setEndValue(0.85);
        }
        else
        {
            // 放大
            currentPixZoomAnimation->setStartValue(1);
            currentPixZoomAnimation->setEndValue(1.15);
        }
        currentPixZoomAnimation->setDuration(150);
        currentPixZoomAnimation->start(QAbstractAnimation::DeleteWhenStopped);

        QPropertyAnimation* currentPixOpacityAnimation = new QPropertyAnimation(this, "pScaleAnimationPixOpacity");
        connect(currentPixZoomAnimation, &QPropertyAnimation::finished, this, [=]() {
            QPropertyAnimation* targetPixOpacityAnimation = new QPropertyAnimation(this, "pScaleAnimationPixOpacity");
            targetPixOpacityAnimation->setStartValue(0);
            targetPixOpacityAnimation->setEndValue(1);
            targetPixOpacityAnimation->setDuration(300);
            targetPixOpacityAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        });
        currentPixOpacityAnimation->setStartValue(1);
        currentPixOpacityAnimation->setEndValue(0);
        currentPixOpacityAnimation->setDuration(150);
        currentPixOpacityAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        break;
    }
    case YyWindowType::Flip:
    {
        QWidget* targetWidget = _containerStackedWidget->widget(nodeIndex);
        _getCurrentStackPix();
        _containerStackedWidget->setCurrentIndex(nodeIndex);
        _getTargetStackPix();
        targetWidget->setVisible(false);
        QPropertyAnimation* flipAnimation = new QPropertyAnimation(this, "pFlipAnimationRatio");
        connect(flipAnimation, &QPropertyAnimation::valueChanged, this, [=]() {
            update();
        });
        connect(flipAnimation, &QPropertyAnimation::finished, this, [=]() {
            _targetStackPix = QPixmap();
            _currentStackPix = QPixmap();
            targetWidget->setVisible(true);
        });
        flipAnimation->setEasingCurve(QEasingCurve::InOutSine);
        flipAnimation->setDuration(650);
        flipAnimation->setStartValue(0);
        flipAnimation->setEndValue(isRouteBack ? -180 : 180);
        flipAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        break;
    }
    case YyWindowType::Blur:
    {
        _targetStackPix = QPixmap();
        _blurEffect->setEnabled(true);
        QPropertyAnimation* blurAnimation = new QPropertyAnimation(this, "pBlurAnimationRadius");
        connect(blurAnimation, &QPropertyAnimation::valueChanged, this, [=]() {
            _blurEffect->setBlurRadius(_pBlurAnimationRadius);
        });
        connect(blurAnimation, &QPropertyAnimation::finished, this, [=]() {
            _blurEffect->setEnabled(false);
        });
        blurAnimation->setEasingCurve(QEasingCurve::InOutSine);
        blurAnimation->setDuration(350);
        blurAnimation->setStartValue(40);
        blurAnimation->setEndValue(2);
        blurAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        QApplication::processEvents();
        _containerStackedWidget->setCurrentIndex(nodeIndex);
        break;
    }
    }
}

void YyCentralStackedWidget::paintEvent(QPaintEvent* event)
{
    QRect targetRect = this->rect();
    targetRect.adjust(1, 1, 10, 10);
    QPainter painter(this);
    painter.save();
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    if (!_isTransparent)
    {
        painter.setPen(QPen(YyThemeColor(_themeMode, BasicBaseLine), 1.5));
        painter.setBrush(YyThemeColor(_themeMode, WindowCentralStackBase));
        if (_isHasRadius)
        {
            painter.drawRoundedRect(targetRect, 10, 10);
        }
        else
        {
            painter.drawRect(targetRect);
        }
    }
    // 切换动画
    if (!_targetStackPix.isNull())
    {
        QPoint centralStackPos = _containerStackedWidget->mapToParent(QPoint(0, 0));
        QRect centralStackRect = QRect(centralStackPos.x(), centralStackPos.y(), _containerStackedWidget->width(), _containerStackedWidget->height());
        QPainterPath clipPath;
        clipPath.addRoundedRect(centralStackRect, 10, 10);
        painter.setClipPath(clipPath);
        switch (_stackSwitchMode)
        {
        case YyWindowType::None:
        {
            break;
        }
        case YyWindowType::Popup:
        {
            painter.drawPixmap(QRect(0, _pPopupAnimationYOffset, width(), _containerStackedWidget->height()), _targetStackPix);
            break;
        }
        case YyWindowType::Scale:
        {
            painter.setOpacity(_pScaleAnimationPixOpacity);
            painter.translate(_containerStackedWidget->rect().center());
            painter.scale(_pScaleAnimationRatio, _pScaleAnimationRatio);
            painter.translate(-_containerStackedWidget->rect().center());
            painter.drawPixmap(centralStackRect, _isDrawNewPix ? _targetStackPix : _currentStackPix);
            break;
        }
        case YyWindowType::Flip:
        {
            QTransform transform;
            transform.translate(centralStackRect.center().x(), 0);
            if (abs(_pFlipAnimationRatio) >= 90)
            {
                transform.rotate(-180 + _pFlipAnimationRatio, Qt::YAxis);
            }
            else
            {
                transform.rotate(_pFlipAnimationRatio, Qt::YAxis);
            }
            transform.translate(-centralStackRect.center().x(), 0);
            painter.setTransform(transform);
            if (abs(_pFlipAnimationRatio) >= 90)
            {
                painter.drawPixmap(centralStackRect, _targetStackPix);
            }
            else
            {
                painter.drawPixmap(centralStackRect, _currentStackPix);
            }
            break;
        }
        case YyWindowType::Blur:
        {
            break;
        }
        }
    }
    painter.restore();
}

void YyCentralStackedWidget::_getCurrentStackPix()
{
    _targetStackPix = QPixmap();
    bool isTransparent = _isTransparent;
    _isTransparent = true;
    _containerStackedWidget->currentWidget()->setVisible(true);
    _currentStackPix = _containerStackedWidget->grab();
    _containerStackedWidget->currentWidget()->setVisible(false);
    _isTransparent = isTransparent;
}

void YyCentralStackedWidget::_getTargetStackPix()
{
    _targetStackPix = QPixmap();
    bool isTransparent = _isTransparent;
    _isTransparent = true;
    _targetStackPix = _containerStackedWidget->grab();
    _isTransparent = isTransparent;
}

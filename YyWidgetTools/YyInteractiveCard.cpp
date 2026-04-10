#include "YyInteractiveCard.h"

#include <QPainter>
#include <QPainterPath>

#include "YyTheme.h"
#include "private/YyInteractiveCardPrivate.h"
Q_PROPERTY_CREATE_Q_CPP(YyInteractiveCard, int, BorderRadius)
Q_PROPERTY_CREATE_Q_CPP(YyInteractiveCard, QString, Title);
Q_PROPERTY_CREATE_Q_CPP(YyInteractiveCard, QString, SubTitle);
Q_PROPERTY_CREATE_Q_CPP(YyInteractiveCard, int, TitlePixelSize);
Q_PROPERTY_CREATE_Q_CPP(YyInteractiveCard, int, SubTitlePixelSize);
Q_PROPERTY_CREATE_Q_CPP(YyInteractiveCard, int, TitleSpacing);
Q_PROPERTY_CREATE_Q_CPP(YyInteractiveCard, QPixmap, CardPixmap);
Q_PROPERTY_CREATE_Q_CPP(YyInteractiveCard, QSize, CardPixmapSize);
Q_PROPERTY_CREATE_Q_CPP(YyInteractiveCard, int, CardPixmapBorderRadius)
Q_PROPERTY_CREATE_Q_CPP(YyInteractiveCard, YyCardPixType::PixMode, CardPixMode);
YyInteractiveCard::YyInteractiveCard(QWidget* parent)
    : QPushButton(parent), d_ptr(new YyInteractiveCardPrivate())
{
    Q_D(YyInteractiveCard);
    d->q_ptr = this;
    d->_pBorderRadius = 6;
    d->_pTitlePixelSize = 15;
    d->_pSubTitlePixelSize = 12;
    setMinimumSize(300, 80);
    d->_pCardPixmapSize = QSize(64, 64);
    d->_pTitleSpacing = 2;
    d->_pCardPixmapBorderRadius = 6;
    d->_pCardPixMode = YyCardPixType::PixMode::Ellipse;
    d->_themeMode = eTheme->getThemeMode();
    setMouseTracking(true);
    connect(eTheme, &YyTheme::themeModeChanged, this, [=](YyThemeType::ThemeMode themeMode) { d->_themeMode = themeMode; });
}

YyInteractiveCard::~YyInteractiveCard()
{
}

void YyInteractiveCard::setCardPixmapSize(int width, int height)
{
    Q_D(YyInteractiveCard);
    d->_pCardPixmapSize = QSize(width, height);
    Q_EMIT pCardPixmapSizeChanged();
}

void YyInteractiveCard::paintEvent(QPaintEvent* event)
{
    Q_D(YyInteractiveCard);
    QPainter painter(this);
    painter.save();
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(underMouse() ? YyThemeColor(d->_themeMode, BasicHoverAlpha) : Qt::transparent);
    painter.drawRoundedRect(rect(), d->_pBorderRadius, d->_pBorderRadius);
    // 图片绘制
    if (!d->_pCardPixmap.isNull())
    {
        painter.save();
        QPainterPath path;
        if (d->_pCardPixMode == YyCardPixType::PixMode::Ellipse)
        {
            path.addEllipse(QPointF(d->_pCardPixmapSize.width() / 2 + 10, height() / 2), d->_pCardPixmapSize.width() / 2, d->_pCardPixmapSize.height() / 2);
            painter.setClipPath(path);
            painter.drawPixmap(QRect(10, (height() - d->_pCardPixmapSize.height()) / 2, d->_pCardPixmapSize.width(), d->_pCardPixmapSize.height()), d->_pCardPixmap); // rect为绘制区域，image为要绘制的图片
        }
        else if (d->_pCardPixMode == YyCardPixType::PixMode::Default)
        {
            painter.drawPixmap(10, (height() - d->_pCardPixmapSize.height()) / 2, d->_pCardPixmapSize.width(), d->_pCardPixmapSize.height(), d->_pCardPixmap);
        }
        else if (d->_pCardPixMode == YyCardPixType::PixMode::RoundedRect)
        {
            path.addRoundedRect(QRectF(10, (height() - d->_pCardPixmapSize.height()) / 2, d->_pCardPixmapSize.width(), d->_pCardPixmapSize.height()), d->_pCardPixmapBorderRadius, d->_pCardPixmapBorderRadius);
            painter.setClipPath(path);
            painter.drawPixmap(10, (height() - d->_pCardPixmapSize.height()) / 2, d->_pCardPixmapSize.width(), d->_pCardPixmapSize.height(), d->_pCardPixmap);
        }
        painter.restore();
    }
    // 文字绘制
    painter.setPen(YyThemeColor(d->_themeMode, BasicText));
    QFont font = this->font();
    font.setWeight(QFont::Bold);
    font.setPixelSize(d->_pTitlePixelSize);
    painter.setFont(font);
    int textStartX = d->_pCardPixmapSize.width() + 26;
    int textWidth = width() - textStartX;
    painter.drawText(QRect(textStartX, rect().y(), textWidth, height() / 2 - d->_pTitleSpacing), Qt::TextWordWrap | Qt::AlignBottom | Qt::AlignLeft, d->_pTitle);
    font.setWeight(QFont::Normal);
    font.setPixelSize(d->_pSubTitlePixelSize);
    painter.setFont(font);
    painter.drawText(QRect(textStartX, height() / 2 + d->_pTitleSpacing, textWidth, height() / 2 - d->_pTitleSpacing), Qt::TextWordWrap | Qt::AlignTop | Qt::AlignLeft, d->_pSubTitle);
    painter.restore();
}

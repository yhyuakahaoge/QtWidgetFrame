#include "YyText.h"

#include <QContextMenuEvent>
#include <QPainter>

#include "YyTheme.h"
#include "private/YyTextPrivate.h"
YyText::YyText(QWidget* parent)
    : QLabel(parent), d_ptr(new YyTextPrivate())
{
    Q_D(YyText);
    d->q_ptr = this;
    d->_pTextStyle = YyTextType::NoStyle;
    d->_pYyIcon = YyIconType::None;
    setObjectName("YyText");
    setStyleSheet("#YyText{background-color:transparent;}");
    QFont textFont = font();
    textFont.setLetterSpacing(QFont::AbsoluteSpacing, d->_textSpacing);
    textFont.setPixelSize(28);
    setFont(textFont);
    setWordWrap(true);
    d->_themeMode = eTheme->getThemeMode();
    d->onThemeChanged(eTheme->getThemeMode());
    connect(eTheme, &YyTheme::themeModeChanged, d, &YyTextPrivate::onThemeChanged);
}

YyText::YyText(QString text, QWidget* parent)
    : YyText(parent)
{
    setText(text);
}

YyText::YyText(QString text, int pixelSize, QWidget* parent)
    : YyText(text, parent)
{
    QFont font = this->font();
    font.setPixelSize(pixelSize);
    setFont(font);
}

YyText::~YyText()
{
}

void YyText::setIsWrapAnywhere(bool isWrapAnywhere)
{
    Q_D(YyText);
    setWordWrap(isWrapAnywhere);
    d->_isWrapAnywhere = isWrapAnywhere;
}

bool YyText::getIsWrapAnywhere() const
{
    Q_D(const YyText);
    return d->_isWrapAnywhere;
}

void YyText::setTextPixelSize(int size)
{
    QFont font = this->font();
    font.setPixelSize(size);
    setFont(font);
}

int YyText::getTextPixelSize() const
{
    return this->font().pixelSize();
}

void YyText::setTextPointSize(int size)
{
    QFont font = this->font();
    font.setPointSize(size);
    setFont(font);
}

int YyText::getTextPointSize() const
{
    return this->font().pointSize();
}

void YyText::setTextStyle(YyTextType::TextStyle textStyle)
{
    Q_D(YyText);
    QFont textFont = font();
    d->_pTextStyle = textStyle;
    switch (textStyle)
    {
    case YyTextType::NoStyle:
    {
        break;
    }
    case YyTextType::Caption:
    {
        textFont.setPixelSize(12);
        break;
    }
    case YyTextType::Body:
    {
        textFont.setPixelSize(13);
        break;
    }
    case YyTextType::BodyStrong:
    {
        textFont.setPixelSize(13);
        textFont.setWeight(QFont::DemiBold);
        break;
    }
    case YyTextType::Subtitle:
    {
        textFont.setPixelSize(20);
        textFont.setWeight(QFont::DemiBold);
        break;
    }
    case YyTextType::Title:
    {
        textFont.setPixelSize(28);
        textFont.setWeight(QFont::DemiBold);
        break;
    }
    case YyTextType::TitlYyrge:
    {
        textFont.setPixelSize(40);
        textFont.setWeight(QFont::DemiBold);
        break;
    }
    case YyTextType::Display:
    {
        textFont.setPixelSize(48);
        textFont.setWeight(QFont::DemiBold);
        break;
    }
    }
    setFont(textFont);
}

YyTextType::TextStyle YyText::getTextStyle() const
{
    Q_D(const YyText);
    return d->_pTextStyle;
}

void YyText::setYyIcon(YyIconType::IconName YyIcon)
{
    Q_D(YyText);
    d->_pYyIcon = YyIcon;
    update();
    Q_EMIT pYyIconChanged();
}

YyIconType::IconName YyText::getYyIcon() const
{
    Q_D(const YyText);
    return d->_pYyIcon;
}

void YyText::paintEvent(QPaintEvent* event)
{
    Q_D(YyText);
    if (palette().color(QPalette::WindowText) != YyThemeColor(d->_themeMode, BasicText))
    {
        d->onThemeChanged(d->_themeMode);
    }
    if (d->_pYyIcon != YyIconType::None)
    {
        QPainter painter(this);
        painter.save();
        painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing | QPainter::TextAntialiasing);
        QFont iconFont = QFont("ElaAwesome");
        iconFont.setPixelSize(this->font().pixelSize());
        painter.setFont(iconFont);
        painter.setPen(YyThemeColor(d->_themeMode, BasicText));
        painter.drawText(rect(), Qt::AlignCenter, QChar((unsigned short)d->_pYyIcon));
        painter.restore();
    }
    else
    {
        if (wordWrap() && d->_isWrapAnywhere)
        {
            QPainter painter(this);
            painter.save();
            painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
            painter.setPen(YyThemeColor(d->_themeMode, BasicText));
            painter.drawText(rect(), Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap | Qt::TextWrapAnywhere, text());
            painter.restore();
        }
        else
        {
            QLabel::paintEvent(event);
        }
    }
}

#include "YyTextPrivate.h"

#include "YyText.h"
#include "YyTheme.h"
#include <QTimer>
YyTextPrivate::YyTextPrivate(QObject* parent)
    : QObject{parent}
{
}

YyTextPrivate::~YyTextPrivate()
{
}

void YyTextPrivate::onThemeChanged(YyThemeType::ThemeMode themeMode)
{
    Q_Q(YyText);
    _themeMode = themeMode;
    QPalette palette = q->palette();
    palette.setColor(QPalette::WindowText, YyThemeColor(_themeMode, BasicText));
    q->setPalette(palette);
}

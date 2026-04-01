#ifndef YyTEXTPRIVATE_H
#define YyTEXTPRIVATE_H

#include <QObject>

#include "YyDef.h"
class YyText;
class YyTextPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(YyText)
    Q_PROPERTY_CREATE_D(YyTextType::TextStyle, TextStyle)
    Q_PROPERTY_CREATE_D(YyIconType::IconName, YyIcon)
public:
    explicit YyTextPrivate(QObject* parent = nullptr);
    ~YyTextPrivate() override;
    Q_SLOT void onThemeChanged(YyThemeType::ThemeMode themeMode);

private:
    YyThemeType::ThemeMode _themeMode;
    bool _isWrapAnywhere{false};
    qreal _textSpacing{0.5};
};

#endif // YyTEXTPRIVATE_H

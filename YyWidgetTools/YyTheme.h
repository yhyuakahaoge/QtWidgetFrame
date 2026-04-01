#ifndef YyTHEME_H
#define YyTHEME_H

#include <QObject>

#include "YyDef.h"
#include "YyProperty.h"
#include "YySingleton.h"

#define eTheme YyTheme::getInstance()
#define YyThemeColor(themeMode, themeColor) eTheme->getThemeColor(themeMode, YyThemeType::themeColor)
class QPainter;
class YyThemePrivate;
class Yy_EXPORT YyTheme : public QObject
{
    Q_OBJECT
    Q_Q_CREATE(YyTheme)
    Q_SINGLETON_CREATE_H(YyTheme)
private:
    explicit YyTheme(QObject* parent = nullptr);
    ~YyTheme();

public:
    void setThemeMode(YyThemeType::ThemeMode themeMode);
    YyThemeType::ThemeMode getThemeMode() const;

    void drawEffectShadow(QPainter* painter, QRect widgetRect, int shadowBorderWidth, int borderRadius);

    void setThemeColor(YyThemeType::ThemeMode themeMode, YyThemeType::ThemeColor themeColor, QColor newColor);
    const QColor& getThemeColor(YyThemeType::ThemeMode themeMode, YyThemeType::ThemeColor themeColor);
Q_SIGNALS:
    Q_SIGNAL void themeModeChanged(YyThemeType::ThemeMode themeMode);
};

#endif // YyTHEME_H

#ifndef YyTHEMEPRIVATE_H
#define YyTHEMEPRIVATE_H

#include <QColor>
#include <QMap>
#include <QObject>

#include "YyDef.h"
class YyTheme;
class YyThemePrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(YyTheme)
public:
    explicit YyThemePrivate(QObject* parent = nullptr);
    ~YyThemePrivate();

private:
    YyThemeType::ThemeMode _themeMode{YyThemeType::Light};
    QColor _lightThemeColorList[43];
    QColor _darkThemeColorList[43];
    void _initThemeColor();
};

#endif // YyTHEMEPRIVATE_H

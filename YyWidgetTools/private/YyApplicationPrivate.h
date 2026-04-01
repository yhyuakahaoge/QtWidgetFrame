#ifndef YyAPPLICATIONPRIVATE_H
#define YyAPPLICATIONPRIVATE_H

#include <QColor>
#include <QIcon>
#include <QObject>

#include "YyDef.h"
class YyApplication;
class YyApplicationPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(YyApplication)
    Q_PROPERTY_CREATE_D(YyApplicationType::WindowDisplayMode, WindowDisplayMode)
    Q_PROPERTY_CREATE_D(QString, YyMicaImagePath)

public:
    explicit YyApplicationPrivate(QObject* parent = nullptr);
    ~YyApplicationPrivate() override;
    Q_SLOT void onThemeModeChanged(YyThemeType::ThemeMode themeMode);
Q_SIGNALS:
    Q_SIGNAL void initMicaBase(QImage img);

protected:
    virtual bool eventFilter(QObject* watched, QEvent* event) override;

private:
    friend class YyMicaBaseInitObject;
    YyThemeType::ThemeMode _themeMode;
    QList<QWidget*> _micaWidgetList;
    QImage _lightBaseImage;
    QImage _darkBaseImage;
    void _initMicaBaseImage(QImage img);
    QRect _calculateWindowVirtualGeometry(QWidget* widget);
    void _updateMica(QWidget* widget, bool isProcessEvent = true);
    void _updateAllMicaWidget();
    void _resetAllMicaWidget();
};

#endif // YyAPPLICATIONPRIVATE_H

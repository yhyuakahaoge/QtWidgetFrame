#ifndef YyAPPLICATION_H
#define YyAPPLICATION_H

#include <QIcon>
#include <QObject>

#include "YyDef.h"
#include "YySingleton.h"
#define eApp YyApplication::getInstance()
class YyApplicationPrivate;
class Yy_EXPORT YyApplication : public QObject
{
    Q_OBJECT
    Q_Q_CREATE(YyApplication)
    Q_SINGLETON_CREATE_H(YyApplication)
    Q_PROPERTY_CREATE_Q_H(YyApplicationType::WindowDisplayMode, WindowDisplayMode)
    Q_PROPERTY_CREATE_Q_H(QString, YyMicaImagePath)
private:
    explicit YyApplication(QObject* parent = nullptr);
    ~YyApplication() override;

public:
    void init();
    void syncWindowDisplayMode(QWidget* widget, bool isSync = true);
    static bool containsCursorToItem(QWidget* item);
};

#endif // YyAPPLICATION_H

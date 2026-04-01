#ifndef YyEVENTBUS_H
#define YyEVENTBUS_H

#include <QObject>
#include <QVariantMap>

#include "YyDef.h"
#include "YyProperty.h"
#include "YySingleton.h"
class YyEventPrivate;
class Yy_EXPORT YyEvent : public QObject
{
    Q_OBJECT
    Q_Q_CREATE(YyEvent)
    Q_PROPERTY_CREATE_Q_H(QString, EventName);
    Q_PROPERTY_CREATE_Q_H(QString, FunctionName);
    Q_PROPERTY_CREATE_Q_H(Qt::ConnectionType, ConnectionType);

public:
    explicit YyEvent(QObject* parent = nullptr);
    explicit YyEvent(QString eventName, QString functionName, QObject* parent = nullptr);
    ~YyEvent() override;
    YyEventBusType::EventBusReturnType registerAndInit();
};

class YyEventBusPrivate;
class Yy_EXPORT YyEventBus : public QObject
{
    Q_OBJECT
    Q_Q_CREATE(YyEventBus)
    Q_SINGLETON_CREATE_H(YyEventBus);

private:
    explicit YyEventBus(QObject* parent = nullptr);
    ~YyEventBus() override;

public:
    YyEventBusType::EventBusReturnType post(const QString& eventName, const QVariantMap& data = {});
    QStringList getRegisteredEventsName() const;

private:
    friend class YyEvent;
};

#endif // YyEVENTBUS_H

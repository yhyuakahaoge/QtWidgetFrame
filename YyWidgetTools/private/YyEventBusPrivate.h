#ifndef YyEVENTBUSPRIVATE_H
#define YyEVENTBUSPRIVATE_H

#include <QMap>
#include <QObject>

#include "YyDef.h"
#include "YyProperty.h"
class YyEvent;
class YyEventPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(YyEvent)
    Q_PROPERTY_CREATE_D(QString, EventName);
    Q_PROPERTY_CREATE_D(QString, FunctionName);
    Q_PROPERTY_CREATE_D(Qt::ConnectionType, ConnectionType);

public:
    explicit YyEventPrivate(QObject* parent = nullptr);
    ~YyEventPrivate();
};

class YyEventBus;
class YyEventBusPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(YyEventBus)
public:
    explicit YyEventBusPrivate(QObject* parent = nullptr);
    ~YyEventBusPrivate();
    YyEventBusType::EventBusReturnType registerEvent(YyEvent* event);
    void unRegisterEvent(YyEvent* event);

private:
    QMap<QString, QList<YyEvent*>> _eventMap;
};

#endif // YyEVENTBUSPRIVATE_H

#include "YyEventBus.h"

#include <QVariant>

#include "YyEventBusPrivate.h"
Q_SINGLETON_CREATE_CPP(YyEventBus);
Q_PROPERTY_CREATE_Q_CPP(YyEvent, QString, EventName);
Q_PROPERTY_CREATE_Q_CPP(YyEvent, QString, FunctionName);
Q_PROPERTY_CREATE_Q_CPP(YyEvent, Qt::ConnectionType, ConnectionType);
YyEvent::YyEvent(QObject* parent)
    : QObject{parent}, d_ptr(new YyEventPrivate())
{
    Q_D(YyEvent);
    d->q_ptr = this;
    d->_pConnectionType = Qt::AutoConnection;
    d->_pFunctionName = "";
    d->_pEventName = "";
}

YyEvent::YyEvent(QString eventName, QString functionName, QObject* parent)
    : QObject{parent}, d_ptr(new YyEventPrivate())
{
    Q_D(YyEvent);
    d->q_ptr = this;
    d->_pConnectionType = Qt::AutoConnection;
    d->_pEventName = eventName;
    d->_pFunctionName = functionName;
}

YyEventBusType::EventBusReturnType YyEvent::registerAndInit()
{
    return YyEventBus::getInstance()->d_ptr->registerEvent(this);
}

YyEvent::~YyEvent()
{
    YyEventBus::getInstance()->d_ptr->unRegisterEvent(this);
}

YyEventBus::YyEventBus(QObject* parent)
    : QObject{parent}, d_ptr(new YyEventBusPrivate())
{
    Q_D(YyEventBus);
    d->q_ptr = this;
}

YyEventBus::~YyEventBus()
{
}

YyEventBusType::EventBusReturnType YyEventBus::post(const QString& eventName, const QVariantMap& data)
{
    Q_D(YyEventBus);
    if (eventName.isEmpty())
    {
        return YyEventBusType::EventBusReturnType::EventNameInvalid;
    }
    if (d->_eventMap.contains(eventName))
    {
        QList<YyEvent*> eventList = d->_eventMap.value(eventName);
        foreach (auto event, eventList)
        {
            if (event->parent())
            {
                QMetaObject::invokeMethod(event->parent(), event->getFunctionName().toLocal8Bit().constData(), event->getConnectionType(), Q_ARG(QVariantMap, data));
            }
        }
    }
    return YyEventBusType::EventBusReturnType::Success;
}

QStringList YyEventBus::getRegisteredEventsName() const
{
    Q_D(const YyEventBus);
    if (d->_eventMap.count() == 0)
    {
        return QStringList();
    }
    QStringList eventsNameList = d->_eventMap.keys();
    return eventsNameList;
}

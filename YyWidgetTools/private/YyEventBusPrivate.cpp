#include "YyEventBusPrivate.h"

#include "YyEventBus.h"
YyEventPrivate::YyEventPrivate(QObject* parent)
    : QObject{parent}
{
}

YyEventPrivate::~YyEventPrivate()
{
}

YyEventBusPrivate::YyEventBusPrivate(QObject* parent)
    : QObject{parent}
{
}

YyEventBusPrivate::~YyEventBusPrivate()
{
}

YyEventBusType::EventBusReturnType YyEventBusPrivate::registerEvent(YyEvent* event)
{
    if (!event)
    {
        return YyEventBusType::EventBusReturnType::EventInvalid;
    }
    if (event->getEventName().isEmpty())
    {
        return YyEventBusType::EventBusReturnType::EventNameInvalid;
    }
    if (_eventMap.contains(event->getEventName()))
    {
        QList<YyEvent*> eventList = _eventMap.value(event->getEventName());
        if (eventList.contains(event))
        {
            return YyEventBusType::EventBusReturnType::EventInvalid;
        }
        eventList.append(event);
        _eventMap[event->getEventName()] = eventList;
    }
    else
    {
        QList<YyEvent*> eventList;
        eventList.append(event);
        _eventMap.insert(event->getEventName(), eventList);
    }
    return YyEventBusType::EventBusReturnType::Success;
}

void YyEventBusPrivate::unRegisterEvent(YyEvent* event)
{
    if (!event)
    {
        return;
    }
    if (event->getEventName().isEmpty())
    {
        return;
    }
    if (_eventMap.contains(event->getEventName()))
    {
        if (_eventMap[event->getEventName()].count() == 1)
        {
            _eventMap.remove(event->getEventName());
        }
        else
        {
            QList<YyEvent*> eventList = _eventMap.value(event->getEventName());
            eventList.removeOne(event);
            _eventMap[event->getEventName()] = eventList;
        }
    }
}

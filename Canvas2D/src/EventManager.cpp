#include "EventManager.h"
#include <type_traits>

EventType BaseEvent::GetStaticType()
{
	return EventType::None;
}

using eventList = std::list<void(*)(BaseEvent*)>;
using eventMap = eventList[EventType::Count];

eventMap EventManager::events;

EventManager* EventManager::instance = NULL;

EventManager* EventManager::Instance()
{
	if (instance == NULL)
	{
		instance = new EventManager();
	}

	return instance;
}
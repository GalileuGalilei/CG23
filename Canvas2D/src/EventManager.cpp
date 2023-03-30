#include "EventManager.h"
#include <type_traits>

EventType BaseEvent::GetStaticType()
{
	return EventType::None;
}

using eventFunc = bool(*)(BaseEvent*);
using eventMap = eventFunc[EventType::Count][LISTENERS_TAM];

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
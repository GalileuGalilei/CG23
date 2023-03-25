#include "EventManager.h"
#include <string>

std::string BaseEvent::GetName()
{
	std::string name = "BaseEvent";
	return name;
}

EventManager* EventManager::instance = NULL;

EventManager* EventManager::Instance()
{
	if (instance == NULL)
	{
		instance = new EventManager();
	}

	return instance;
}

void EventManager::InvokeEvent(BaseEvent* baseEvent)
{
	auto functions = events[baseEvent->GetName()];

	for (auto f : functions)
	{
		f(baseEvent);
	}
}

void EventManager::AddListener(BaseEvent* baseEvent,void (*func)(BaseEvent*))
{
	if (events.find(baseEvent->GetName()) == events.end())
	{
		events.emplace(std::make_pair(baseEvent->GetName(), new std::list<void (*)(BaseEvent*)>{ func }));
	}
	else
	{
		events[baseEvent->GetName()].push_back(func);
	}
}

void EventManager::RemoveListener(BaseEvent* baseEvent, void (*func)(BaseEvent*))
{
	if (events.find(baseEvent->GetName()) == events.end())
	{
		events[baseEvent->GetName()].remove(func);
	}
}
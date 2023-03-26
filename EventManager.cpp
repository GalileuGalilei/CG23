#include "EventManager.h"
#include <string>

std::string BaseEvent::GetName()
{
	std::string str = "BaseEvent";
	return str;
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

void EventManager::InvokeEvent(std::string eventName, BaseEvent* baseEvent)
{
	auto functions = events[eventName];

	for (auto f : functions)
	{
		f(baseEvent);
	}
}

void EventManager::AddListener(std::string eventName, void (*func)(BaseEvent*))
{	
	if (events.find(eventName) == events.end())
	{
		events.emplace(std::make_pair(eventName, new std::list<void (*)(BaseEvent*)>{ func }));
	}
	else
	{
		events[eventName].push_back(func);
	}
}

void EventManager::RemoveListener(std::string eventName, void (*func)(BaseEvent*))
{
	if (events.find(eventName) == events.end())
	{
		events[eventName].remove(func);
	}
}
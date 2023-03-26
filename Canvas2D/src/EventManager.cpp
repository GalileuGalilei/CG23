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

void EventManager::InvokeEvent(BaseEvent* baseEvent)
{
	auto functions = events[baseEvent->GetName()];

	for (auto f : functions)
	{
		f(baseEvent);
	}
}

template <typename T> void EventManager::AddListener(void (*func)(T*))
{
	static_assert(std::is_base_of<BaseEvent, T>, "deve ser derivada de BaseEvent");
	
	if (events.find(T::GetName() == events.end())
	{
		events.emplace(std::make_pair(T::GetName, new std::list<void (*)(T*)>{ func }));
	}
	else
	{
		events[T::GetName()].push_back(func);
	}
}

template <typename T> void EventManager::RemoveListener(void (*func)(T*))
{
	static_assert(std::is_base_of<BaseEvent, T>, "deve ser derivada de BaseEvent");

	if (events.find(T::GetName()) == events.end())
	{
		events[T::GetName()].remove(func);
	}
}
#ifndef EVENT_MANAGER
#define EVENT_MANAGER

#include <list>
#include <type_traits>

enum EventType
{
	None = 0,
	ClickEvent,
	RenderEvent,
	Count
};

/// <summary>
/// classe base para a criação de eventos globais que podem ser usados pelo EventManager
/// </summary>
class BaseEvent
{
public:
	/// <summary>
	/// retorna o nome do evento. Isso é necessário para diferenciar os eventos
	/// </summary>
 	virtual EventType GetType() const = 0;
	static EventType GetStaticType();

protected:
	BaseEvent() {};
};

using EvenFunc = void(*)(BaseEvent*);
using EventList = std::list<EvenFunc>;
using EventMap = EventList[EventType::Count];

/// <summary>
/// Singleton que controla todos os eventos globais
/// </summary>
class EventManager
{
	EventManager(EventManager* other) = delete;
	void operator=(const EventManager*) = delete;
	
private:
	static EventManager* instance;
	static EventMap eventMap;
	EventManager() 
	{

	};

public:

	static EventManager* Instance();

	template <typename T>
	void InvokeEvent(BaseEvent* baseEvent)
	{
		if (!std::is_base_of<BaseEvent, T>())
		{
			printf("ERRO, o tipo passado não é compatível com BaseEvent\n\n");
			return;
		}

		if (T::GetStaticType() != baseEvent->GetType() || T::GetStaticType() == EventType::None)
		{
			printf("ERRO: template do evento não corresponde com o tipo do argumento\n\n");
			return;
		}

		EventType type = T::GetStaticType();
		EventList eventList = EventManager::eventMap[type];

		//printf("tamanho do evento: %i", eventList.size());
		for (EvenFunc f : eventList)
		{
			f(baseEvent);
		}
	}

	template<typename T>
	void AddListener(EvenFunc func)
	{
		if (!std::is_base_of<BaseEvent, T>())
		{
			printf("ERRO, o tipo passado não é compatível com BaseEvent\n\n");
			return;
		}

		EventType type = T::GetStaticType();
		EventList* eventList = &EventManager::eventMap[type];
		eventList->push_back(func);
	}

	template<typename T>
	void RemoveListener(EvenFunc func)
	{
		if (!std::is_base_of<BaseEvent, T>())
		{
			printf("ERRO, o tipo passado não é compatível com BaseEvent\n\n");
			return;
		}

		EventType type = T::GetStaticType();
		EventList* eventList = &EventManager::eventMap[type];
		eventList->remove(func);
	}
};


#endif // !EVENT_MANAGER
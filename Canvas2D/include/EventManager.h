#ifndef EVENT_MANAGER
#define EVENT_MANAGER
#define LISTENERS_TAM 8

#include <map>
#include <list>
#include <string>
#include <functional>
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


/// <summary>
/// Singleton que controla todos os eventos globais
/// </summary>
class EventManager
{
	using eventFunc = void(*)(BaseEvent*);
	using eventMap = eventFunc[EventType::Count][LISTENERS_TAM];

	//singleton não pode ser copiável ou assinalável
	EventManager(EventManager* other) = delete;
	void operator=(const EventManager*) = delete;
	
private:
	static EventManager* instance;
	static eventMap events;
	EventManager() 
	{
		for (int i = 0; i < EventType::Count; i++)
		{
			for (int j = 0; j < LISTENERS_TAM; j++)
			{
				EventManager::events[i][j] = NULL;
			}
		}
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
			printf("ERRO: tipo do evento não correspondente\n\n");
			return;
		}

		EventType type = T::GetStaticType();

		auto functions = EventManager::events[type];

		for (int i = 0; i < LISTENERS_TAM; i++)
		{
			if (functions[i] == NULL)
			{
				return;
			}

			functions[i](baseEvent);
		}
	}

	template<typename T>
	void AddListener(eventFunc func)
	{
		if (!std::is_base_of<BaseEvent, T>())
		{
			printf("ERRO, o tipo passado não é compatível com BaseEvent\n\n");
			return;
		}

		EventType type = T::GetStaticType();

		auto functions = EventManager::events[type];

		for (int i = 0; i < LISTENERS_TAM; i++)
		{
			if (functions[i] == NULL)
			{
				functions[i] = func;
				return;
			}
		}
	}

	template<typename T>
	void RemoveListener(void (*func)(T*))
	{
		if (!std::is_base_of<BaseEvent, T>())
		{
			printf("ERRO, o tipo passado não é compatível com BaseEvent\n\n");
			return;
		}

		EventType type = T::GetStaticType();
		auto functions = EventManager::events[type];

		for (int i = 0; i < LISTENERS_TAM - 1; i++)
		{
			if (functions[i] == func)
			{
				functions[i] = functions[i + 1];
				functions[i] = func;
			}
		}

		if (functions[LISTENERS_TAM - 1] == func)
		{
			functions[LISTENERS_TAM - 1] = NULL;
		}
	}
};


#endif // !EVENT_MANAGER
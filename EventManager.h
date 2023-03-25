#pragma once
#include <map>
#include <list>
#include <string>

/// <summary>
/// classe base para a criação de eventos globais que podem ser usados pelo EventManager
/// </summary>
class BaseEvent
{
public:
	BaseEvent() = delete;


	/// <summary>
	/// retorna o nome do evento. Isso é necessário para deferenciar os eventos
	/// </summary>
	virtual std::string GetName() = 0;
};


/// <summary>
/// Singleton que controla todos os eventos globais
/// </summary>
class EventManager
{
	//singleton não pode ser copiável ou assinalável
	EventManager(EventManager* other) = delete;
	void operator=(const EventManager*) = delete;

private:
	static EventManager* instance;
	static std::map<std::string, std::list<void (*)(BaseEvent*)>> events;
	EventManager() {};

public:
	static EventManager* Instance();

	void InvokeEvent(BaseEvent* baseEvent);
	void AddListener(BaseEvent* baseEvent, void (*func)(BaseEvent*));
	void RemoveListener(BaseEvent* baseEvent, void (*func)(BaseEvent*));
};

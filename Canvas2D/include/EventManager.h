#pragma once
#include <map>
#include <list>
#include <string>

/// <summary>
/// classe base para a cria��o de eventos globais que podem ser usados pelo EventManager
/// </summary>
class BaseEvent
{
public:
	BaseEvent() {};
	/// <summary>
	/// retorna o nome do evento. Isso � necess�rio para diferenciar os eventos
	/// </summary>
 	static std::string GetName();

};


/// <summary>
/// Singleton que controla todos os eventos globais
/// </summary>
class EventManager
{
	//singleton n�o pode ser copi�vel ou assinal�vel
	EventManager(EventManager* other) = delete;
	void operator=(const EventManager*) = delete;

private:
	static EventManager* instance;
	static std::map<std::string, std::list<void (*)(BaseEvent*)>> events;
	EventManager() {};

public:
	static EventManager* Instance();

	void InvokeEvent(BaseEvent* baseEvent);
	template <typename T> void AddListener(void (*func)(T*));
	template <typename T> void RemoveListener(void (*func)(T*));
};


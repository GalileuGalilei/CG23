#pragma once
#include "EventManager.h"
class OnRenderEvent : BaseEvent
{
public:

	static EventType GetStaticType();

	EventType GetType() const override
	{
		return GetStaticType();
	}

	OnRenderEvent() {}
};

class OnClickEvent : BaseEvent
{
public :

	static EventType GetStaticType();

	EventType GetType() const override
	{
		return GetStaticType();
	}

	int button, state, x, y;

	OnClickEvent(int button, int state, int x, int y)
	{
		this->button = button;
		this->state = state;
		this->x = x;
		this->y = y;
	}
};


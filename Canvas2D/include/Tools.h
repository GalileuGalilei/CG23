#pragma once
#include "EventManager.h"
#include "GameEvents.h"
#include "ConcavePolygon.h"

class OnToolEvent : public BaseEvent
{
public:


	OnClickEvent* click;
	static EventType GetStaticType();

	EventType GetType() const override
	{
		return GetStaticType();
	}

	OnToolEvent(OnClickEvent* click)
	{
		//this->polygon = polygon;
		this->click = click;
	}
};

class MoveTool : IRenderable
{
public:
	static void OnTool(BaseEvent* baseEvent);
};


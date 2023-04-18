#pragma once
#include "EventManager.h"
#include "GameEvents.h"
#include "PolygonShape.h"

class OnToolEvent : public BaseEvent
{
public:

	PolygonShape* polygon;
	OnClickEvent* click;
	OnMouseOverEvent* mouseOver;
	static EventType GetStaticType();

	EventType GetType() const override
	{
		return GetStaticType();
	}

	OnToolEvent(PolygonShape* polygon, OnClickEvent* click, OnMouseOverEvent* mouseOver)
	{
		this->polygon = polygon;
		this->click = click;
		this->mouseOver = mouseOver;
	}
};

class MoveTool
{
public:
	static void OnTool(BaseEvent* baseEvent);
};

class RotateTool 
{
public:
	static void OnTool(BaseEvent* baseEvent);
};

class ScaleTool
{
public:
	static void OnTool(BaseEvent* baseEvent);
};




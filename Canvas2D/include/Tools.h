#pragma once
#include "EventManager.h"
#include "GameEvents.h"

class MoveTool : IRenderable
{
public:
	static void OnTool(BaseEvent* baseEvent);
};


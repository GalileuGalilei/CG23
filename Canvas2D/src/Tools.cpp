#include "Tools.h"

EventType OnToolEvent::GetStaticType()
{
	return EventType::ToolEvent;
}

void MoveTool::OnTool(BaseEvent* baseEvent)
{
	OnToolEvent* args = (OnToolEvent*)baseEvent;
}
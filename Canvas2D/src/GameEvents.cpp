#include "GameEvents.h"

EventType OnClickEvent::GetStaticType()
{
	return EventType::ClickEvent;
}

EventType OnRenderEvent::GetStaticType()
{
	return EventType::RenderEvent;
}

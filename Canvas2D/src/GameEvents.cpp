#include "GameEvents.h"

EventType OnRenderEvent::GetStaticType()
{
	return EventType::RenderEvent;
}

std::list<IRenderable*> IRenderable::renderList;
void IRenderable::RenderAll(BaseEvent* baseEvent)
{
	OnRenderEvent* args = (OnRenderEvent*)baseEvent;

	for (auto i : IRenderable::renderList)
	{
		i->OnRender(args);
	}
}

EventType OnClickEvent::GetStaticType()
{
	return EventType::ClickEvent;
}

std::list<IClickable*> IClickable::clickList;
void IClickable::ClickAll(BaseEvent* baseEvent)
{
	OnClickEvent* args = (OnClickEvent*)baseEvent;

	for (auto i : IClickable::clickList)
	{
		i->OnClick(args);
	}
}

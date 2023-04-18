#include "Tools.h"

EventType OnToolEvent::GetStaticType()
{
	return EventType::ToolEvent;
}

void MoveTool::OnTool(BaseEvent* baseEvent)
{
	OnToolEvent* args = (OnToolEvent*)baseEvent;
	PolygonShape* polygon = (PolygonShape*)args->polygon;
	OnClickEvent* click = args->click;

	polygon->SetPosition(Vector2(click->x, click->y));
}

void RotateTool::OnTool(BaseEvent* baseEvent)
{
	OnToolEvent* args = (OnToolEvent*)baseEvent;
	PolygonShape* polygon = (PolygonShape*)args->polygon;
	//OnClickEvent* click = args->click;


	
	//polygon->SetRotation(click->x);
}

void ScaleTool::OnTool(BaseEvent* baseEvent)
{
	OnToolEvent* args = (OnToolEvent*)baseEvent;
	PolygonShape* polygon = (PolygonShape*)args->polygon;
	OnClickEvent* click = args->click;
	OnMouseOverEvent* mouseOver = args->mouseOver;
	Vector2 scale = mouseOver->translation;

	if (click->button != -2)
	{
		polygon->Scale(scale);
	}
}

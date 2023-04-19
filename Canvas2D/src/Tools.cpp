#include "Tools.h"

std::list<ITool*> ITool::toolList;
PolygonShape* ITool::selectedPolygon = NULL; 

EventType OnToolEvent::GetStaticType()
{
	return EventType::ToolEvent;
}

bool MoveTool::isMoving = false;

void MoveTool::OnMoveTool(BaseEvent* baseEvent)
{
	if (selectedPolygon == NULL)
	{
		return;
	}

	if (baseEvent->GetType() == ClickEvent)
	{
		OnClickEvent* click = (OnClickEvent*)baseEvent;
		if (!isMoving)
		{
			isMoving = true;
		}
		else
		{
			isMoving = false;
			selectedPolygon = NULL;
		}
	}
	else if (baseEvent->GetType() == MouseOverEvent)
	{
		OnMouseOverEvent* mouseOver = (OnMouseOverEvent*)baseEvent;
		if (isMoving)
		{
			selectedPolygon->SetPosition(Vector2(mouseOver->x, mouseOver->y));
		}
	}
}

bool RotateTool::isRotating = false;

void RotateTool::OnRotateTool(BaseEvent* baseEvent)
{
	const float pixelToRadians = 1 / (3.141526 * 2);

	if (selectedPolygon == NULL)
	{
		return;
	}

	if (baseEvent->GetType() == ClickEvent)
	{
		OnClickEvent* click = (OnClickEvent*)baseEvent;
		if (!isRotating)
		{
			isRotating = true;
		}
		else
		{
			isRotating = false;
			selectedPolygon = NULL;
		}
	}
	else if (baseEvent->GetType() == MouseOverEvent)
	{
		OnMouseOverEvent* mouseOver = (OnMouseOverEvent*)baseEvent;

		if (isRotating && mouseOver->wheel != -2)
		{
			selectedPolygon->Rotate(mouseOver->wheel * pixelToRadians);
		}
	}
}

Vector2 ScaleTool::previousMouse = Vector2(-1, -1);

void ScaleTool::OnScaleTool(BaseEvent* baseEvent)
{
	OnClickEvent* click = (OnClickEvent*)baseEvent;
	Vector2 currentMouse = Vector2(click->x, click->y);
	Vector2 scale = currentMouse - previousMouse;
	previousMouse = currentMouse;

	if (previousMouse.x < 0)
	{
		return;
	}

	selectedPolygon->Scale(scale);
}

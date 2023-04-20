#include "Tools.h"

std::list<ITool*> ITool::toolList;
PolygonShape* ITool::selectedPolygon = NULL; 

EventType OnToolEvent::GetStaticType()
{
	return EventType::ToolEvent;
}


void FillTool::OnFillTool(BaseEvent* baseEvent)
{
	if (selectedPolygon == NULL)
	{
		return;
	}
	
	selectedPolygon->Fill();
	selectedPolygon->SetColor(ColorDisplay::selectedColor);
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

bool ScaleTool::isScaling = false;

void ScaleTool::OnScaleTool(BaseEvent* baseEvent)
{
	const float scaleFactor = 100;

	if (selectedPolygon == NULL)
	{
		return;
	}

	if (baseEvent->GetType() == ClickEvent)
	{
		OnClickEvent* click = (OnClickEvent*)baseEvent;
		if (!isScaling && click->state == 1)
		{
			isScaling = true;
		}
		else
		{
			isScaling = false;
			selectedPolygon = NULL;
		}
	}
	else if (baseEvent->GetType() == MouseOverEvent && isScaling)
	{
		OnMouseOverEvent* mouseOver = (OnMouseOverEvent*)baseEvent;
		Vector2 scale = mouseOver->translation;

		scale = Vector2(-scale.x / scaleFactor, -scale.y / scaleFactor);
		scale.x = scale.x < 0 ? 1 - scale.x : 1 / (1 + scale.x);
		scale.y = scale.y < 0 ? 1 - scale.y : 1 / (1 + scale.y);
		
		selectedPolygon->Scale(scale);
	}
}

#include "Tools.h"
#include "DrawableDisplay.h"

std::list<ITool*> ITool::toolList;
std::list<PolygonShape*> ITool::polygonList;
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

void DeleteTool::OnDeleteTool(BaseEvent* baseEvent)
{
	if (selectedPolygon == NULL)
	{
		return;
	}

	OnKeyEvent* args = (OnKeyEvent*)baseEvent;

	if (args->key == 127 && args->state == 0)
	{
		EditablePolygon* p = (EditablePolygon*)selectedPolygon;
		polygonList.remove(p);
		delete(p);
		selectedPolygon = NULL;
	}
}

char SaveTool::savePath[] = "figuras.gr";

void SaveTool::OnSaveTool(BaseEvent* baseEvent)
{
	FILE* f;

	fopen_s(&f, savePath, "wb");

	for (auto polygon : polygonList)
	{
		EditablePolygon* editable = (EditablePolygon*)polygon;
		PolygonData data = editable->GetData();
		fwrite(&data, sizeof(PolygonData), 1, f);
		fwrite(editable->points[0].data(), sizeof(float), data.tam, f);
		fwrite(editable->points[1].data(), sizeof(float), data.tam, f);
	}
	fclose(f);

	selectedPolygon = NULL;
}

SaveTool::SaveTool()
{
	FILE* f;
	fopen_s(&f, savePath, "rb");

	if (f == NULL)
	{
		return;
	}

	while (!feof(f))
	{
		PolygonData data;
		fread(&data, sizeof(PolygonData), 1, f);

		if (data.tam < 1)
		{
			break;
		}

		std::vector<float> x(data.tam);
		std::vector<float> y(data.tam);

		fread(x.data(), sizeof(float), data.tam, f);
		fread(y.data(), sizeof(float), data.tam, f);

		EditablePolygon* polygon = new EditablePolygon();
		polygon->LoadData(data, x, y);
		polygonList.push_back(polygon);
	}

	fclose(f);
}
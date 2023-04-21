#include "DrawableDisplay.h"

DrawTool::DrawTool(Vector2 position, Vector2 size)
{
	this->position = position;
	this->size = size;
	editablePolygon = new EditablePolygon();
	previewPolygon = new PolygonShape(std::vector<Vector2>());
	previewPolygon->SetColor(previewColor);
	previewPolygon->isFilled = false;
	RemoveToolListeners();
}

void DrawTool::AddPoint(OnClickEvent* args)
{
	if (args->button == 0)
	{
		if (previewPolygon->tam == 0)
		{
			AddPreviewPoint(args);
		}

		if (editablePolygon->AddPoint(Vector2(args->x, args->y)))
		{
			AddPreviewPoint(args);
		}
	}
	else
	{
		if (editablePolygon->tam < 3)
		{
			delete(editablePolygon);
		}
		else
		{
			polygonList.push_back(editablePolygon);
		}

		selectedPolygon = NULL;
		editablePolygon = new EditablePolygon();
		previewPolygon->points[0].clear();
		previewPolygon->points[1].clear();
		previewPolygon->tam = 0;
	}
}

bool DrawTool::CheckBounds(int x, int y)
{
	if (x > position.x + size.x || x < position.x)
	{
		return false;
	}

	if (y > position.y + size.y || y < position.y)
	{
		return false;
	}

	return true;
}

void DrawTool::AddPreviewPoint(OnClickEvent* args)
{
	previewPolygon->points[0].push_back(args->x);
	previewPolygon->points[1].push_back(args->y);
	previewPolygon->tam++;
	previewPolygon->RemoveRenderListener();
	previewPolygon->AddRenderListener();

	if (previewPolygon->tam == 3)
	{
		previewPolygon->SetColor(Colors::black);
		previewPolygon->isFilled = true;
	}
	else
	{
		previewPolygon->SetColor(previewColor);
		previewPolygon->isFilled = false;
	}
}
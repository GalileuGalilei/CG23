#pragma once
#include "Vector2.h"
#include "Polygon.h"
#include "gl_canvas2d.h"
#include "Botao.h"
#include "ToolBar.h"
#include "GameEvents.h"

/// <summary>
/// Essa classe contém todas as funções e instâncias de calsses necessárias para criar
/// </summary>
class DrawableDisplay : IClickable
{
private:
	Vector2 position;
	Vector2 size;
	EditablePolygon* editablePolygon;

	bool IsInsertPolygonEnable = true;

public:

	/// <param name="position">posição do canto inferior esquerdo </param>
	/// <param name="size">dimenções de largura e altura do display </param>
	DrawableDisplay(Vector2 position, Vector2 size)
	{
		this->position = position;
		this->size = size;
		editablePolygon = new EditablePolygon(std::vector<Vector2>());
	}

	void OnClick(OnClickEvent* args) override
	{
		if (!CheckBounds(args->x, args->y) || !IsInsertPolygonEnable)
		{
			return;
		}

		AddPoint(args);
	}

	void OnMouseOver(OnMouseOverEvent* args) override
	{
		if (editablePolygon->tam < 1 || !IsInsertPolygonEnable)
		{
			return;
		}

		editablePolygon->points[0][editablePolygon->tam - 1] = args->x;
		editablePolygon->points[1][editablePolygon->tam - 1] = args->y;
	}

private:

	bool CheckBounds(int x, int y)
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

	void AddPoint(OnClickEvent* args)
	{
		if (args->button == 0)
		{	
			editablePolygon->points[0].push_back(args->x);
			editablePolygon->points[1].push_back(args->y);
			editablePolygon->tam++;

			if (editablePolygon->tam > 4)
			{
				editablePolygon->Triangulate();
			}

			if (editablePolygon->tam == 1)
			{
				AddPoint(args);
			}
		}
		else
		{
			editablePolygon = new EditablePolygon(std::vector<Vector2>());
		}
	}
};

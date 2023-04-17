#pragma once
#include "Vector2.h"
#include "EditablePolygon.h"
#include "gl_canvas2d.h"
#include "Botao.h"
#include "ToolBar.h"
#include "GameEvents.h"

/// <summary>
/// Essa classe contém todas as funções e instâncias de calsses necessárias para criar e editar um polígono
/// </summary>
class DrawableDisplay : IClickable
{
private:
	Vector2 position;
	Vector2 size;
	EditablePolygon* editablePolygon;

	bool IsInsertPolygonEnable = true;

public:

	DrawableDisplay(Vector2 position, Vector2 size)
	{
		this->position = position;
		this->size = size;
		editablePolygon = new EditablePolygon();
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

		editablePolygon->SetPointPosition(Vector2(args->x, args->y), editablePolygon->tam - 1);
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
			if (editablePolygon->tam > 2)
			{
				editablePolygon->RemoveLastPoint();
			}

			editablePolygon->AddPoint(Vector2(args->x, args->y));
			editablePolygon->points[0].push_back(args->x);
			editablePolygon->points[1].push_back(args->y);
			editablePolygon->tam++;
		}
		else
		{
			editablePolygon->RemoveLastPoint();
			editablePolygon = new EditablePolygon();
		}
	}
};

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
	PolygonShape* editablePolygon;

	bool IsInsertPolygonEnable = false;

public:

	/// <param name="position">posição do canto inferior esquerdo </param>
	/// <param name="size">dimenções de largura e altura do display </param>
	DrawableDisplay(Vector2 position, Vector2 size)
	{
		this->position = position;
		this->size = size;
		editablePolygon = new PolygonShape(NULL, NULL, 0);
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
			int newTam;
			if (editablePolygon->tam == 0)
			{
				newTam = 2;
			}
			else
			{
				newTam = editablePolygon->tam + 1;
			}


			float* x = (float*)malloc(sizeof(float) * newTam);
			float* y = (float*)malloc(sizeof(float) * newTam);

			
			for (int i = 0; i < editablePolygon->tam; i++)
			{
				x[i] = editablePolygon->points[0][i];
				y[i] = editablePolygon->points[1][i];
			}

			x[newTam - 1] = args->x;
			y[newTam - 1] = args->y;

			if (editablePolygon->tam > 0)
			{
				free(editablePolygon->points[0]);
				free(editablePolygon->points[1]);
			}

			if (editablePolygon->tam == 0)
			{
				x[newTam - 2] = args->x;
				y[newTam - 2] = args->y;
			}

			editablePolygon->points[0] = x;
			editablePolygon->points[1] = y;
			editablePolygon->tam = newTam;
		}
		else
		{
			editablePolygon = new PolygonShape(NULL, NULL, 0);
		}
	}
};

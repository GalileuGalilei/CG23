#pragma once
#include "Vector2.h"
#include "EditablePolygon.h"
#include "gl_canvas2d.h"
#include "Botao.h"
#include "GameEvents.h"

/// <summary>
/// Essa classe cont�m todas as fun��es e inst�ncias de calsses necess�rias para criar e editar um pol�gono
/// </summary>
class DrawableDisplay : IClickable
{
private:
	Vector2 position;
	Vector2 size;
	EditablePolygon* editablePolygon;
	EditablePolygon* tempPolygon;

	bool IsInsertPolygonEnable = true;

public:

	DrawableDisplay(Vector2 position, Vector2 size)
	{
		this->position = position;
		this->size = size;
		editablePolygon = new EditablePolygon();
		tempPolygon = new EditablePolygon();
	}

	void SetState(bool state)
	{
		IsInsertPolygonEnable = state;
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
		if (tempPolygon->tam < 1 || !IsInsertPolygonEnable)
		{
			return;
		}

		tempPolygon->SetPointPosition(Vector2(args->x, args->y), tempPolygon->tam - 1);
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
			if (tempPolygon->tam == 0)
			{
				tempPolygon->points[0].push_back(args->x);
				tempPolygon->points[1].push_back(args->y);
				tempPolygon->tam++;
			}

			if (editablePolygon->AddPoint(Vector2(args->x, args->y)))
			{
				tempPolygon->points[0].push_back(args->x);
				tempPolygon->points[1].push_back(args->y);
				tempPolygon->tam++;
			}
		}
		else
		{
			editablePolygon = new EditablePolygon();
			tempPolygon->Erase();
		}
	}
};

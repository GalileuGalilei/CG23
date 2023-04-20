#pragma once
#include "Vector2.h"
#include "EditablePolygon.h"
#include "gl_canvas2d.h"
#include "Botao.h"
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
	EditablePolygon* tempPolygon;
	std::list<EditablePolygon*> drawnPolygons;
	const char* savePath = "figuras.gr";

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

	//escreva uma função que salve todos os poligonos da lista 	std::list<EditablePolygon*> drawnPolygons em um arquivo
	void SaveDisplay()
	{
		FILE* f = fopen(savePath, "wb");
		
		for (auto polygon : drawnPolygons)
		{
			PolygonData data = polygon->GetData();
			fwrite(&data, sizeof(PolygonData), 1, f);
			fwrite(polygon->points[0].data(), sizeof(float), data.tam, f);
			fwrite(polygon->points[1].data(), sizeof(float), data.tam, f);
		}
		fclose(f);
	}

	void LoadDisplay()
	{
		FILE* f = fopen(savePath, "rb");
		
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
			drawnPolygons.push_back(polygon);
		}
		
		fclose(f);
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
			drawnPolygons.push_back(editablePolygon);
			editablePolygon = new EditablePolygon();
			tempPolygon->Erase();
		}
	}
};

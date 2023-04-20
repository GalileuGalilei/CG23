#include "EditablePolygon.h"

Color EditablePolygon::selectedColor = Color(0.6, 0.1, 0.6);

PolygonData EditablePolygon::GetData()
{
	PolygonData data = PolygonData 
	(
		tam,
		isFilled,
		isCenterCalculated,
		center,
		color
	);

	return data;
}

void EditablePolygon::LoadData(PolygonData data, std::vector<float> x, std::vector<float> y)
{
	this->Erase();
	
	tam = data.tam;
	color = data.color;
	isFilled = data.isFilled;
	isCenterCalculated = data.isCenterCalculated;
	center = data.center;

	this->points[0] = x;
	this->points[1] = y;

	this->Triangulate();
}

bool EditablePolygon::AddPoint(Vector2 point)
{
	if (!IsValiblePoint(point))
	{
		printf("ERRO: ponto inválido");
		return false;
	}

	points[0].push_back(point.x);
	points[1].push_back(point.y);
	tam++;
	if (!Triangulate())
	{
		RemoveLastPoint();
		return false;
	}

	return true;
}

void EditablePolygon::RemoveLastPoint()
{
	if (tam == 0)
	{
		return;
	}

	points[0].pop_back();
	points[1].pop_back();
	tam--;
	Triangulate();
}

void EditablePolygon::SetPointPosition(Vector2 pos, int index)
{
	points[0][index] = pos.x;
	points[1][index] = pos.y;
}

void EditablePolygon::Erase()
{
	points[0].clear();
	points[1].clear();
	triangles.clear();
	tam = 0;
}

void DrawBorder(Color color)
{
	
}
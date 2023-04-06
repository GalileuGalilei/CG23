#include "Polygon.h"
#include "gl_canvas2d.h"

void PolygonShape::Translate(Vector2 vector)
{
	for (int i = 0; i < tam; i++)
	{
		points[0][i] += vector.x;
		points[1][i] += vector.y;
	}
}

void PolygonShape::SetPosition(Vector2 pos)
{
	Vector2 t = pos - Vector2(points[0][0], points[1][0]);
	this->Translate(t);
}

void PolygonShape::Fill()
{
	isFilled = true;
}

void PolygonShape::SetColor(Color color)
{
	this->color = color;
}

void PolygonShape::SetColor(float r, float g, float b)
{
	this->color = Color(r, g, b);
}

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

void PolygonShape::Fill()
{
	isFilled = true;
}

bool PolygonShape::PointToPolygon(Vector2 vector)
{
	return false;
}

void PolygonShape::SetColor(float R, float G, float B)
{
	this->R = R;
	this->G = G;
	this->B = B;
}

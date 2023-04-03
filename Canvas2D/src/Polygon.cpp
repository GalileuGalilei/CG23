#include "Polygon.h"
#include "gl_canvas2d.h"

std::list<PolygonShape*> PolygonShape::polygons = std::list<PolygonShape*>();

void PolygonShape::Render()
{
	CV::color(R, G, B);
	if (isFilled)
	{
		CV::polygonFill(points[0], points[1], tam);
	}
	else
	{
		CV::polygon(points[0], points[1], tam);
	}
}

void PolygonShape::RenderPolygonsListener(BaseEvent* baseEvent)
{
	for (auto i : PolygonShape::polygons)
	{
		i->Render();
	}
}

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

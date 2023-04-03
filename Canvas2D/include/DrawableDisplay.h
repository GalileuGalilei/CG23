#pragma once
#include "Vector2.h"
#include "Polygon.h"
#include "gl_canvas2d.h"
#include "GameEvents.h"

class DrawableDisplay : IClickable, IRenderable
{
private:
	Vector2 position;
	Vector2 size;
	PolygonShape* editablePolygon;
	

public:

	/// <param name="position">posição do canto inferior esquerdo </param>
	/// <param name="size">dimenções de largura e altura do display </param>
	DrawableDisplay(Vector2 position, Vector2 size)
	{
		this->position = position;
		this->size = size;
	}

	void OnRender(BaseEvent* baseEvent)
	{
		CV::color(0.5, 0.5, 0.5);
		CV::rectFill(position, position + size);
	}

	void OnClick(BaseEvent* baseEvent)
	{
		printf("bah meu brother, nem sei \n\n");
	}

};


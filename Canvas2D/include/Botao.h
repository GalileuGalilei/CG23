#ifndef __BOTAO_H__
#define __BOTAO_H__

#include "gl_canvas2d.h"
#include "PolygonShape.h"
class Button : IRenderable, IClickable
{
private:
	void(*callback)();

protected:
    const float mouseOverColorChange = 0; //o quanto a cor escurece 

	char label[100];
	bool isMouseOver = false;
	Color color;
	Vector2 position, size;
	PolygonShape* polygon;

public:
  Button(Vector2 position, Vector2 size, Color color, const char label[], void(*callback)())
  {
     strcpy_s(this->label, 100, label);

     this->position = position;
	 this->size = size;
     this->color = color;
     this->polygon = new PolygonShape(position, size);
     this->polygon->SetColor(color);
	 this->callback = callback;
  }

  void OnRender(OnRenderEvent* args) override
  {
      CV::color(0, 0, 0);
      CV::text(position.x+5, position.y + size.y / 2, label);
  }

  void OnClick(OnClickEvent* args) override
  {
	  if (!CheckBounds(args->x, args->y))
	  {
		  return;
	  }

	  //polygon->SetColor(color.r * mouseOverColorChange, color.g * mouseOverColorChange, color.b * mouseOverColorChange);
	  printf("botao!\n");
	  callback();
  }

  void OnMouseOver(OnMouseOverEvent* args) override
  {
	  if (!CheckBounds(args->x, args->y))
	  {
		  return;
	  }
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

};

#endif

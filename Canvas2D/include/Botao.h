#ifndef __BOTAO_H__
#define __BOTAO_H__

#include "gl_canvas2d.h"
#include "PolygonShape.h"
#include <functional>
class Button : IRenderable, IClickable 
{
private:
	std::function<void()> callback;

protected:

	const float offset = 0.2f;
	char label[100];
	bool isMouseOver = false;
	Color color;
	Color normalColor;
	Color pressedColor;
	Vector2 position, size;

public:
  Button(Vector2 position, Vector2 size, Color color, const char label[], std::function<void()> callback)
  {
     strcpy_s(this->label, 100, label);

     this->position = position;
	 this->size = size;
     this->color = color;
	 normalColor = color;
	 this->callback = callback;

	 pressedColor = Color(color.r - offset, color.g - offset, color.b - offset);
  }

  void OnRender(OnRenderEvent* args) override
  {
	  CV::color(color.r, color.g, color.b);
	  CV::rectFill(position, position + size);
      CV::color(0, 0, 0);
      CV::text(position.x+5, position.y + size.y / 2, label);
  }

  void OnClick(OnClickEvent* args) override
  {
	  if (!CheckBounds(args->x, args->y))
	  {
		  color = normalColor;
		  return;
	  }
	  
	  color = pressedColor;
	  callback();
  }

  void OnMouseOver(OnMouseOverEvent* args) override
  {
	  if (!CheckBounds(args->x, args->y))
	  {
		  return;
	  }
  }

  GameLayer GetLayer() override
  {
	  return GameLayer::UI;
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

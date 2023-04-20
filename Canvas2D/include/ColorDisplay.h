#pragma once
#include "gl_canvas2d.h"
#include "GameEvents.h"
#include <cmath>

class ColorDisplay : IRenderable, IClickable
{
	Vector2 position;
	Vector2 size;
    Vector2 selectedColorDisplaySize;

public:
        static Color selectedColor;

		ColorDisplay(Vector2 position, Vector2 size)
		{
			this->position = position;
            this->size = Vector2(size.x, size.y - size.x);;
            selectedColorDisplaySize = Vector2(size.x, size.x);
		}

        Color PickColor(Vector2 pos)
        {
            float r = 0, g = 0, b = 0;

            float ratio = (pos.y - position.y) / size.y;
            int section = int(ratio * 6.0f);

            float ft = (ratio * 6.0f) - section;
            float aa = 1.0f - ft;

            switch (section)
            {
                case 0: r = 1.0f; g = ft;    b = 0.0f;  break;
                case 1: r = aa;    g = 1.0f; b = 0.0f;  break;
                case 2: r = 0.0f;  g = 1.0f; b = ft;    break;
                case 3: r = 0.0f;  g = aa;   b = 1.0f;  break;
                case 4: r = ft;    g = 0.0f; b = 1.0f;  break;
                case 5: r = 1.0f;  g = 0.0f; b = aa;    break;
            }

            return Color(r, g, b);
        }

private:


    void OnRender(OnRenderEvent* args) override
    {
        for (int x = position.x; x < position.x + size.x; x++)
        {
            for (int y = position.y; y < position.y + size.y; y++)
            {
                Color rgb = PickColor(Vector2(x, y));
                CV::color(rgb.r, rgb.g, rgb.b, 1);
                CV::point(x, y);
            }
        }

        CV::color(selectedColor.r, selectedColor.g, selectedColor.b, 1);
        Vector2 pos = Vector2(position.x, position.y + size.y);
        CV::rectFill(pos, selectedColorDisplaySize + pos);
    }

    GameLayer GetLayer() override
    {
		return GameLayer::UI2;
	}

    void OnClick(OnClickEvent* args) override
    {
        if (args->x >= position.x && args->x <= position.x + size.x &&
            args->y >= position.y && args->y <= position.y + size.y)
        {
			selectedColor = PickColor(Vector2(args->x, args->y));
		}
	}
    void OnMouseOver(OnMouseOverEvent* args) override
    {
        return;
	}
   
};


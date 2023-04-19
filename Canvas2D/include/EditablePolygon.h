#ifndef EDITABLE_POLYGON
#define EDITABLE_POLYGON

#include <vector>
#include "Vector2.h"
#include "ConcavePolygon.h"
#include "Tools.h"

class EditablePolygon : public ConcavePolygon, public IClickable
{
public:

	EditablePolygon(std::vector<Vector2> points) : ConcavePolygon(points) {}

	EditablePolygon() : ConcavePolygon(std::vector<Vector2>()) {}
	
	static Color selectedColor;

	void AddPoint(Vector2 point);
	void RemoveLastPoint();
	void SetPointPosition(Vector2 pos, int index);
	void Erase();

private:

	bool isSelected = false;

	void PushToFrontLayer()
	{
		RemoveRenderListener();
		AddRenderListener();
	}

	void OnRender(OnRenderEvent* args) override
	{				
		CV::color(color.r, color.g, color.b);

		RenderTriangles();
		float* x = points[0].data();
		float* y = points[1].data();

		if (isSelected)
		{
			CV::color(selectedColor.r, selectedColor.g, selectedColor.b);
			CV::polygon(x, y, tam);
			return;
		}
	}

	void OnClick(OnClickEvent* args) override
	{
		if (!PointToPolygon(Vector2(args->x, args->y), NULL))
		{
			isSelected = false;
			return;
		}

		isSelected = true;
		PushToFrontLayer();
		EventManager::Instance()->InvokeEvent<OnToolEvent>((BaseEvent*) new OnToolEvent(this));
	}

	OnMouseOverEvent* lastMouseOverEvent = NULL;

	void OnMouseOver(OnMouseOverEvent* args) override
	{
		lastMouseOverEvent = args;
	}
};


#endif // !EDITABLE_POLYGON

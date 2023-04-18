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

	void AddPoint(Vector2 point);
	void RemoveLastPoint();
	void SetPointPosition(Vector2 pos, int index);
	void Erase();

private:

	void OnRender(OnRenderEvent* args) override
	{
		CV::color(color.r, color.g, color.b);

		if (isFilled)
		{
			RenderTriangles();
			return;
		}

		float* x = points[0].data();
		float* y = points[1].data();

		CV::polygon(x, y, tam);
	}

	void OnClick(OnClickEvent* args) override
	{
		if (!PointToPolygon(Vector2(args->x, args->y), NULL))
		{
			return;
		}

		EventManager::Instance()->InvokeEvent<OnToolEvent>((BaseEvent*) new OnToolEvent(this, args, lastMouseOverEvent));
	}

	OnMouseOverEvent* lastMouseOverEvent = NULL;

	void OnMouseOver(OnMouseOverEvent* args) override
	{
		lastMouseOverEvent = args;
	}
};


#endif // !EDITABLE_POLYGON

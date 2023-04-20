#ifndef EDITABLE_POLYGON
#define EDITABLE_POLYGON

#include <vector>
#include "Vector2.h"
#include "ConcavePolygon.h"
#include "Tools.h"

/// <summary>
/// classe usada para carregar e descarregar poligonos de um arquivo
/// </summary>
struct PolygonData
{
	int tam;
	Color color;
	bool isFilled;
	bool isCenterCalculated;
	Vector2 center;

	PolygonData()
	{
		tam = 0;
		isFilled = true;
		isCenterCalculated = false;
		center = Vector2(0, 0);
		color = Colors::black;
	}

	PolygonData(int tam, bool isFilled, bool isCenterCalculated, Vector2 center, Color color)
	{
		this->tam = tam;
		this->color = color;
		this->isFilled = isFilled;
		this->isCenterCalculated = isCenterCalculated;
		this->center = center;
	}
};

class EditablePolygon : public ConcavePolygon, public IClickable
{
public:

	EditablePolygon(std::vector<Vector2> points) : ConcavePolygon(points) {}

	EditablePolygon() : ConcavePolygon(std::vector<Vector2>()) {}
	
	static Color selectedColor;

	PolygonData GetData();
	void LoadData(PolygonData data, std::vector<float> x, std::vector<float> y);
	bool AddPoint(Vector2 point);
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
			//isSelected = false;
			return;
		}

		isSelected = true;
		EventManager::Instance()->InvokeEvent<OnToolEvent>((BaseEvent*) new OnToolEvent(this));
	}

	OnMouseOverEvent* lastMouseOverEvent = NULL;

	void OnMouseOver(OnMouseOverEvent* args) override
	{
		lastMouseOverEvent = args;
	}

	GameLayer GetLayer() override
	{
		return GameLayer::Default;
	}
};


#endif // !EDITABLE_POLYGON

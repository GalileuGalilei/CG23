#ifndef DRAWABLE_DISPLAY
#define DRAWABLE_DISPLAY

#include "Vector2.h"
#include "EditablePolygon.h"
#include "gl_canvas2d.h"
#include "Botao.h"
#include "GameEvents.h"
#include "Tools.h"

/// <summary>
/// Essa classe contém todas as funções necessárias para criar e editar um polígono qualquer.
/// Como ela é um pouco mais complexa que as outras ferramentas(ITools), ela foi separada em um arquivo próprio.
/// </summary>
class DrawTool : ITool, IClickable
{
private:
	Vector2 position;
	Vector2 size;

	EditablePolygon* editablePolygon;
	PolygonShape* previewPolygon;
	const Color previewColor = Color(0.8, 0.2, 0.8);

	bool CheckBounds(int x, int y);
	void AddPoint(OnClickEvent* args);
	void AddPreviewPoint(OnClickEvent* args);

public:

	DrawTool(Vector2 position, Vector2 size);

	void OnClick(OnClickEvent* args) override
	{
		if (!CheckBounds(args->x, args->y))
		{
			return;
		}

		AddPoint(args);
	}

	void OnMouseOver(OnMouseOverEvent* args) override
	{
		if (previewPolygon->tam < 1)
		{
			return;
		}

		int tam = previewPolygon->tam;
		previewPolygon->points[0][tam - 1] = args->x;
		previewPolygon->points[1][tam - 1] = args->y;
	}

	void RemoveToolListeners() override
	{
		RemoveClickListener();
	}

	void AddToolListeners() override
	{
		AddClickListener();
	}
};

#endif // !DRAWABLE_DISPLAY

#ifndef POLYGON_SHAPE
#define POLYGON_SHAPE

#include "Vector2.h"
#include "gl_canvas2d.h"
#include <vector>
#include "GameEvents.h"

/////////////////////////////////////////////////////////////////////////////////////////////
// obs: foi usado o nome polygonShape para evitar conflitos com a classe Polygon do OpenGL //
/////////////////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// classe que define uma base para polygonos quaisquer
/// </summary>
class PolygonShape : IRenderable
{
protected:
	std::vector<float> points[2]; // [0] = x; [1] = y;
	Color color = Colors::black;
	int tam = 0;
	bool isFilled = false;

public:

	void Translate(Vector2 vector);
	void SetPosition(Vector2 pos);
	void SetColor(Color color);
	void SetColor(float r, float g, float b);
	void Fill();

	friend class DrawableDisplay;

	PolygonShape(std::vector<Vector2> points);

	/// <summary>
	/// cria um polígono no formato de um retângulo
	/// </summary>
	PolygonShape(Vector2 position, Vector2 size);

	/// <summary>
	/// verifica se uma linha está dentro do polígono
	/// </summary>
	bool LineToPolygon(Vector2 p1, Vector2 p2, std::vector<bool>* ignoreIndex);

	/// <summary>
	/// conta o número de interseções entre uma linha e o polígono
	/// </summary>
	int LineIntersectingCount(Vector2 p1, Vector2 q1, std::vector<bool>* ignoreIndex);

	/// <summary>
	/// verifica se um ponto está dentro do polígono
	/// </summary>
	bool PointToPolygon(Vector2 point, std::vector<bool>* ignoreIndex);

private:

	void OnRender(OnRenderEvent* args) override
	{
		float* x = points[0].data();
		float* y = points[1].data();

		CV::color(color.r, color.g, color.b);
		if (isFilled)
		{
			CV::polygonFill(x, y, tam);
		}
		else
		{
			CV::polygon(x, y, tam);
		}
	}
};


#endif // !POLYGON_SHAPE


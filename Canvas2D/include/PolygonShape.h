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
class PolygonShape : public IRenderable
{
protected:
	std::vector<float> points[2]; // [0] = x; [1] = y;
	Vector2 center;
	Color color = Colors::black;
	int tam = 0;
	bool isFilled = true;
	bool isCenterCalculated = false;

public:

	void Translate(Vector2 vector);
	void SetPosition(Vector2 pos);
	void Rotate(float angle);
	void Scale(Vector2 scale);
	void SetColor(Color color);
	void SetColor(float r, float g, float b);
	void Fill();

	friend class SaveTool;
	friend class DrawTool;

	PolygonShape(std::vector<Vector2> points);

	/// <summary>
	/// cria um pol�gono no formato de um ret�ngulo
	/// </summary>
	PolygonShape(Vector2 position, Vector2 size);

	/// <summary>
	/// verifica se uma linha est� dentro do pol�gono
	/// </summary>
	bool LineToPolygon(Vector2 p1, Vector2 p2, std::vector<bool>* ignoreIndex);

	/// <summary>
	/// conta o n�mero de interse��es entre uma linha e o pol�gono
	/// </summary>
	int LineIntersectingCount(Vector2 p1, Vector2 q1, std::vector<bool>* ignoreIndex);

	/// <summary>
	/// verifica se um ponto est� dentro do pol�gono
	/// </summary>
	bool PointToPolygon(Vector2 point, std::vector<bool>* ignoreIndex);
	
protected:
	int Orientation(Vector2 p1, Vector2 p2, Vector2 p3);
	bool IsLineIntersecting(Vector2 p1, Vector2 p2, Vector2 q1, Vector2 q2);

private:

	/// <summary>
	/// calcula a posi��o central do pol�gono
	/// </summary>
	void CalculateCenter();

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


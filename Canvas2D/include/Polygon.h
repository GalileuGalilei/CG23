#pragma once
#include "Vector2.h"
#include "EventManager.h"
#include "GameEvents.h"
#include "gl_canvas2d.h"
#include <vector>

/// <summary>
/// classe que define uma base para polygonos cônvacos
/// </summary>
class PolygonShape : IRenderable
{
protected:
	std::vector<float> points[2]; // [0] = x; [1] = y;
	Color color = Colors::black;
	int tam = 0;
	bool isFilled = true;

public:

	/// <summary>
	/// verifica se um ponto está dentro do polígono
	/// </summary>
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
	/// verifica se um ponto está dentro do polígono
	/// </summary>
	bool PointToPolygon(Vector2 point);

private:

	//verifica se um ponto está dentro de um retângulo delimitado por dois pontos(um segmento)
	bool OnLine(Vector2 p1, Vector2 p2, Vector2 p3);
	int Orientation(Vector2 p1, Vector2 p2, Vector2 p3);
	bool IsLineIntersecting(Vector2 p1, Vector2 q1, Vector2 p2, Vector2 q2);

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

class EditablePolygon : PolygonShape
{
protected:
	int* triangules;
	int tamTriangules;

public:




private:
	void Triangulate()
	{
		if (tam < 3)
		{
			return;
		}

		std::vector<int> triangules;
		std::vector<float> aux[2];

		for (int i = 0; i < tam; i++)
		{
			aux[0].push_back(points[0][i]);
			aux[1].push_back(points[1][i]);
		}

		int j = 0;
		while (tam > 3)
		{
			//remove o ponto na posição j do poligono
			int auxX = points[0][j];
			int auxY = points[1][j];

			tam = points->size();
			j = (j + 1) % tam;
		}
	}

	void OnRender(OnRenderEvent* args) override
	{

	}
};
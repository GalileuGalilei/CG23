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
	bool PointToPolygon(Vector2 point, std::list<int>* ignoreIndex);

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

class EditablePolygon : public PolygonShape
{
protected:
	std::vector<int> triangles;

public:

	EditablePolygon(std::vector<Vector2> points) : PolygonShape(points)
	{

	}

	void Triangulate()
	{
		if (tam < 3)
		{
			return;
		}

		int j = 0;
		std::list<int> ignoreIndex;
		while (ignoreIndex.size() < tam - 3)
		{
			ignoreIndex.push_back(j);

			if (!PointToPolygon(Vector2(points[0][j], points[1][j]), &ignoreIndex))
			{
				triangles.push_back(j);
				triangles.push_back((j + 1) % tam);
				triangles.push_back((j + 2) % tam);
			}
			else
			{
				ignoreIndex.pop_back();
			}

			j = (j + 1) % tam;
		}
		return;
		printf("\nfim de loop");
		for (int i = 0; i < tam; i++)
		{
			bool ignore = false;
			for (int index : ignoreIndex)
			{
				if (index == i)
				{
					ignore = true;
					break;
				}
			}

			if (!ignore)
			{
				triangles.push_back(i);
			}
		}
	}
private:
	void OnRender(OnRenderEvent* args) override
	{
		float* x = points[0].data();
		float* y = points[1].data();

		if (tam < 4)
		{
			CV::polygon(x, y, tam);
			return;
		}

		int triangulesTam = triangles.size();
		float triangle[2][3];

		for (int i = 0; i < triangulesTam; i += 3)
		{
			triangle[0][0] = points[0][triangles[i]];
			triangle[0][1] = points[0][triangles[i + 1]];
			triangle[0][2] = points[0][triangles[i + 2]];

			triangle[1][0] = points[1][triangles[i]];
			triangle[1][1] = points[1][triangles[i + 1]];
			triangle[1][2] = points[1][triangles[i + 2]];

			CV::polygon(triangle[0], triangle[1], 3);
		}
	}
};
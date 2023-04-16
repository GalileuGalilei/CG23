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

class EditablePolygon : public PolygonShape
{
protected:
	std::vector<int> triangles;

public:

	EditablePolygon(std::vector<Vector2> points) : PolygonShape(points) {}

	//verifica se o novo ponto é valido(se não criaria um poligono auto intersectante)
	bool IsNewPointValiable(Vector2 newPoint)
	{
		return true;
	}

	void Triangulate()
	{
		if (tam < 3)
		{
			return;
		}

		int valiblePoints = tam;
		triangles.clear();

		std::vector<bool> ignoreIndex;
		for (int i = 0; i < tam; i++)
		{
			ignoreIndex.push_back(false);
		}

		int i2 = 0;

		while (valiblePoints > 3)
		{
			if (ignoreIndex[i2])
			{
				i2 = (i2 + 1) % tam;
				continue;
			}

			int i1 = 0;
			int i3 = 0;

			FindValibleTriangle(&i1, &i3, i2, ignoreIndex);

			Vector2 p1 = Vector2(points[0][i1], points[1][i1]);
			Vector2 p2 = Vector2(points[0][i3], points[1][i3]);
			Vector2 dir = p1 - p2;

			dir.normalize();
			p1 = p1 - dir;
			p2 = p2 + dir;

			if (LineToPolygon(p1, p2, &ignoreIndex)) //significa que a linha está totalmente dentro do polígono
			{
				valiblePoints--;

				triangles.push_back(i1);
				triangles.push_back(i2);
				triangles.push_back(i3);

				ignoreIndex[i2] = true;
			}

			i2 = (i2 + 1) % tam;
		}

		for (int i = 0; i < tam; i++)
		{
			if (!ignoreIndex[i])
			{
				triangles.push_back(i);
			}
		}
	}
private:

	//acha dois vertices disponíveis que possam formar um triangulo com i2
	void FindValibleTriangle(int* i1, int* i3, int i2, std::vector<bool> ignoreIndex)
	{
		*i3 = i2;
		*i1 = i2;

		while (true)
		{
			if (ignoreIndex[*i3] || *i3 == i2)
			{
				*i3 = (*i3 + 1) % tam;
				continue;
			}

			if (ignoreIndex[*i1] || *i1 == i2)
			{
				(*i1)--;

				if (*i1 < 0)
				{
					*i1 = tam - 1;
				}

				continue;
			}

			if (*i1 == *i3)
			{
				printf("ERRO: não há vertices disponíveis o suficiente para criar um triângulo");

				*i3 = 0;
				*i1 = 0;

				return;
			}

			return;
		}
	}

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


#pragma once
#include "Vector2.h"
#include "EventManager.h"
#include "GameEvents.h"
#include "gl_canvas2d.h"

/// <summary>
/// classe que define uma base para polygonos cônvacos
/// </summary>
class PolygonShape : IRenderable
{
protected:
	float* points[2]; //points[0] = x; points[1] = y  (coordenadas absolutas)
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

	PolygonShape(float* x, float* y, int tam)
	{
		this->tam = tam;
		points[0] = x;
		points[1] = y;
	}

	/// <summary>
	/// cria um polígono no formato de um retângulo
	/// </summary>
	PolygonShape(Vector2 position, Vector2 size)
	{
		float* x = new float[4];
		float* y = new float[4];

		Vector2 ab = position;
		Vector2 ba = position + size;

		x[0] = ab.x;
		x[1] = ab.x;
		x[2] = ba.x;
		x[3] = ba.x;

		y[0] = ab.y;
		y[1] = ba.y;
		y[2] = ba.y;
		y[3] = ab.y;

		points[0] = x;
		points[1] = y;
		tam = 4;
	}

private:
	void OnRender(OnRenderEvent* args) override
	{
		CV::color(color.r, color.g, color.b);
		if (isFilled)
		{
			CV::polygonFill(points[0], points[1], tam);
		}
		else
		{
			CV::polygon(points[0], points[1], tam);
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
		std::list<int> triangules;


	}

	void OnRender(OnRenderEvent* args) override
	{

	}
};
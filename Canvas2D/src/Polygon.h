#pragma once
#include "Vector2.h"
#include "EventManager.h"
#include "GameEvents.h"
#include <list>

/// <summary>
/// classe que define uma base para polygonos cônvacos
/// </summary>
class PolygonShape
{
protected:
	float* points[2]; //points[0] = x; points[1] = y(coordenadas absolutas)
	float R, G, B;
	int tam = 0;
	bool isFilled = false;

public:

	/// <summary>
	/// verifica se um ponto está dentro do polígono
	/// </summary>
	void Translate(Vector2 vector);
	void SetColor(float R, float G, float B);
	void Fill();

	virtual bool PointToPolygon(Vector2 vector);
	virtual void Render();

	static std::list<PolygonShape*> polygons;
	static void RenderPolygonsListener(BaseEvent* baseEvent);

	PolygonShape(float* x, float* y, int tam)
	{
		this->tam = tam;
		points[0] = x;
		points[1] = y;

		R = 0;
		G = 0;
		B = 0;

		polygons.push_back(this);
	}

	/// <summary>
	/// cria um polígono no formato de um retângulo
	/// </summary>
	/// <param name="ab">canto inferio esquerdo</param>
	/// <param name="ba">canto superior direito</param>
	PolygonShape(Vector2 ab, Vector2 ba)
	{
		float* x = new float[4];
		float* y = new float[4];

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

		R = 0;
		G = 0;
		B = 0;

		polygons.push_back(this);
	}

	~PolygonShape()
	{
		polygons.remove(this);
	}
};

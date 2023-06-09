#ifndef CONCAVE_POLYGON
#define CONCAVE_POLYGON

#include "PolygonShape.h"

class ConcavePolygon : public PolygonShape
{
public:

	ConcavePolygon(std::vector<Vector2> points) : PolygonShape(points) 
	{
		if (!IsValiblePolygon())
		{
			this->points[0] = std::vector<float>();
			this->points[1] = std::vector<float>();

			printf("ERRO: poligono inv�lido (auto intersecta)");
			return;
		}

		Triangulate();
	}

protected:

	std::vector<int> triangles;

	/// <summary>
	/// insere os indices dos triangulos no vetor triangles usando o algoritmo ear-clipping
	/// </summary>
	bool Triangulate();

	/// <summary>
	/// verifica se o ponto pode ser adicionado ao poligono sem causar auto intersec��o
	/// </summary>
	bool IsValiblePoint(Vector2 point);

	/// <summary>
	/// Renderiza os triangulos dos poligonos
	/// </summary>
	void RenderTriangles();

private:

	/// <summary>
	/// verifica se o poligono em quest�o � valido(n�o se auto intersecta)
	/// </summary>
	bool IsValiblePolygon();

	/// <summary>
	/// tenta achar o triangulo v�lido mais pr�ximo de i2, sendo o triangulo formador pelos v�rtices (i1,i2,i3)
	/// </summary>
	bool FindValibleTriangle(int* i1, int* i3, int i2, std::vector<bool> ignoreIndex);

	/// <summary>
	/// verifica se um ponto em cima de uma linha � um ponto do poligono
	/// </summary>
	/// <param name="p1"></param>
	/// <returns></returns>
	bool PointToLinePolygon(Vector2 p1);

	void OnRender(OnRenderEvent* args) override
	{
		RenderTriangles();
	}
};


#endif // ! CONCAVE_POLYGON

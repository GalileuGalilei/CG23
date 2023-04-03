#ifndef __BOTAO_H__
#define __BOTAO_H__

#include "gl_canvas2d.h"
#include "Polygon.h"

class Botao : PolygonShape
{
  float altura, largura, x, y;
  char label[100];
  

public:
  Botao(float _x, float _y, float _larg, float _alt, char *_label) :
  PolygonShape(Vector2(_x, _y), Vector2(_x + _larg, _y + _alt))
  {
     isFilled = true;
     altura  = _alt;
     largura = _larg;
     x = _x;
     y = _y;
     strcpy(label, _label);
  }

  void Render() override
  {
      PolygonShape::Render();
      CV::color(0, 0, 0);
      CV::text(x+5, y+altura/2, label); //escreve o label do botao mais ou menos ao centro.
  }
};

#endif

/*********************************************************************
// Canvas2D
// Autor: Cesar Tadeu Pozzer
//        04/2021
// *********************************************************************/
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gl_canvas2d.h"
#include "EventManager.h"
#include "GameEvents.h"
#include "DrawableDisplay.h"
#include "PolygonShape.h" //refatorar nome



//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis
//globais que podem ser setadas pelo metodo keyboard()
void render()
{
    EventManager::Instance()->InvokeEvent<OnRenderEvent>((BaseEvent*) new OnRenderEvent());
}


//funcao chamada toda vez que uma tecla for pressionada
void keyboard(int key)
{
   printf("\nClicou Tecla: %d" , key);
}


//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
   printf("\nLiberou Tecla: %d" , key);
}


//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
    if (state == 1)
    {
        EventManager::Instance()->InvokeEvent<OnClickEvent>((BaseEvent*) new OnClickEvent(button, state, x, y));
    }

    EventManager::Instance()->InvokeEvent<OnMouseOverEvent>((BaseEvent*) new OnMouseOverEvent(x, y));
}

int main(void)
{
    int screenWidth = 500, screenHeight = 500; //largura e altura inicial da tela. Alteram com o redimensionamento de tela.

    EventManager::Instance()->AddListener<OnRenderEvent>(IRenderable::RenderAll);
    EventManager::Instance()->AddListener<OnClickEvent>(IClickable::ClickAll);
    EventManager::Instance()->AddListener<OnMouseOverEvent>(IClickable::MouseOverAll);
    DrawableDisplay display = DrawableDisplay(Vector2(25, 25), Vector2(450, 450));
    ToolBar toolBar = ToolBar(Vector2(0, 0), Vector2(40, screenHeight), 5);

    CV::init(&screenWidth, &screenHeight, "Canvas 2D");
    CV::run();
}

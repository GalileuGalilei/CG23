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





//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis
//globais que podem ser setadas pelo metodo keyboard()
void render()
{
    color(4);
    circleFill( 100, 100, 40, 20);
    circleFill( 160, 160, 30, 5);
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{

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

class OnMouseEvent : BaseEvent
{
public:

    static std::string GetName()
    {
        std::string name = "OnMouseEvent";
        return name;
    }

    int button;
    int state; 
    int wheel; 
    int direction; 
    int x; 
    int y;

    OnMouseEvent(int button, int state, int wheel, int direction, int x, int y)
    {
        this->button = button;
        this->direction = direction;
        this->state = state;
        this->wheel = wheel;
        this->x = x; 
        this->y = y;
    }
};

void OnMouseEventListener(OnMouseEvent* args)
{
    printf("\nmouse %d %d %d %d %d %d", args->button, args->state, args->wheel, args->direction, args->x, args->y);
}

int main(void)
{
    EventManager::Instance()->AddListener<OnMouseEvent>(OnMouseEventListener);
   int screenWidth = 500, screenHeight = 500; //largura e altura inicial da tela. Alteram com o redimensionamento de tela.
   init(&screenWidth, &screenHeight, "Canvas 2D");
   run();
}

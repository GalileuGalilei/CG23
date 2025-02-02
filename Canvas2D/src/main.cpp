#define _CRT_SECURE_NO_WARNINGS
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gl_canvas2d.h"
#include "EventManager.h"
#include "GameEvents.h"
#include "DrawableDisplay.h"
#include "ToolBar.h"
#include "PolygonShape.h" 

void render()
{
    EventManager::Instance()->InvokeEvent<OnRenderEvent>((BaseEvent*) new OnRenderEvent());
}

void keyboard(int key)
{
	EventManager::Instance()->InvokeEvent<OnKeyEvent>((BaseEvent*) new OnKeyEvent(key, 0));
}

void keyboardUp(int key)
{
    EventManager::Instance()->InvokeEvent<OnKeyEvent>((BaseEvent*) new OnKeyEvent(key, 1));
}

void mouse(int button, int state, int wheel, int direction, int x, int y)
{
    if (state == 1)
    {
        EventManager::Instance()->InvokeEvent<OnClickEvent>((BaseEvent*) new OnClickEvent(button, state, x, y));
    }

    EventManager::Instance()->InvokeEvent<OnMouseOverEvent>((BaseEvent*) new OnMouseOverEvent(x, y, direction));
}

int main(void)
{
    int screenWidth = 800, screenHeight = 500;

    EventManager::Instance()->AddListener<OnRenderEvent>(IRenderable::RenderAll);
    EventManager::Instance()->AddListener<OnClickEvent>(IClickable::ClickAll);
    EventManager::Instance()->AddListener<OnMouseOverEvent>(IClickable::MouseOverAll);
    ToolBar toolBar = ToolBar(screenWidth, screenHeight, 70, 5);

    CV::init(&screenWidth, &screenHeight, "Canvas 2D");
    CV::run();
}

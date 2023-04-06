#pragma once
#include "gl_canvas2d.h"
#include "GameEvents.h"
#include "Botao.h"
#include <list>

class ToolBar
{
private :
	std::list<Button> buttonList;
	Vector2 position, size;

public :
	ToolBar(Vector2 postion, Vector2 size)
	{
		this->position = position;
		this->size = size;
	}

	void AddButton()
	{

	}
};


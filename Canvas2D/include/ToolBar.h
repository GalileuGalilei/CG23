#pragma once
#include "gl_canvas2d.h"
#include "GameEvents.h"
#include "Botao.h"
#include <list>

class ToolBar : IRenderable
{
private :
	std::list<Button*> buttonList;
	Vector2 position, size;
	Vector2 buttonSize;
	const int offset;

public :
	ToolBar(Vector2 postion, Vector2 size, int buttonOffset) : offset(buttonOffset)
	{
		this->position = position;
		this->size = size;
		buttonSize = Vector2(size.x - offset, size.x - offset);
		SetToolButtons();
	}


private:

	void OnRender(OnRenderEvent* args) override
	{
		Color c = Colors::yellow;
		CV::color(c.r, c.g, c.b);
		CV::rectFill(position.x, position.y, size.x + offset, size.y);
	}

	void SetToolButtons()
	{
		AddButton([]() {printf("lambda callback 1"); }, Colors::green);
		AddButton([]() {printf("lambda callback 2"); }, Colors::red);
		AddButton([]() {printf("lambda callback 3"); }, Colors::orange);
	}

	void AddButton(void(*callback)(), Color color)
	{
		int y = size.x * buttonList.size() + offset;
		int x = position.x + offset;
		Button* b = new Button(Vector2(x, y), buttonSize, color, "*", callback);
		buttonList.push_back(b);
	}
};


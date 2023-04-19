#pragma once
#include "gl_canvas2d.h"
#include "GameEvents.h"
#include "Tools.h"
#include "Botao.h"
#include "DrawableDisplay.h"
#include <functional>
#include <list>

class ToolBar : IRenderable
{
private :
	std::list<Button*> buttonList;
	Vector2 position, size;
	Vector2 buttonSize;
	DrawableDisplay* display;
	const int offset;

	MoveTool* moveTool;
	RotateTool* rotateTool;
	ScaleTool* scaleTool;

public :
	ToolBar(DrawableDisplay* display, Vector2 postion, Vector2 size, int buttonOffset) : offset(buttonOffset)
	{
		this->position = position;
		this->size = size;
		this->display = display;
		buttonSize = Vector2(size.x - offset, size.x - offset);
		SetToolButtons();

		EventManager::Instance()->AddListener<OnToolEvent>(ITool::OnTool);

		moveTool = new MoveTool();
		rotateTool = new RotateTool();
		scaleTool = new ScaleTool();
	}

	~ToolBar()
	{
		for (Button* b : buttonList)
		{
			delete b;
		}

		buttonList.clear();
	}

private:

	void OnRender(OnRenderEvent* args) override
	{
		Color c = Colors::yellow;
		CV::color(c.r, c.g, c.b);
		CV::rectFill(position.x, position.y, size.x + offset, size.y);
	}

	void AddButton(std::function<void()> callback, Color color)
	{
		int y = size.x * buttonList.size() + offset;
		int x = position.x + offset;
		Button* b = new Button(Vector2(x, y), buttonSize, color, "*", callback);
		buttonList.push_back(b);
	}

	void SetToolButtons()
	{
		AddButton([this]() 
			{
				ITool::DisableAllTools();
				moveTool->AddToolListeners();
				display->SetState(false);
			}, Colors::green);

		AddButton([this]() 
			{
				ITool::DisableAllTools();
				rotateTool->AddToolListeners();
				display->SetState(false);
			}, Colors::red);

		AddButton([this]() 
			{
				ITool::DisableAllTools();
				scaleTool->AddToolListeners();
				display->SetState(false);
			}, Colors::orange);

		AddButton([this]()
			{
				ITool::DisableAllTools();
				display->SetState(true);
			}, Colors::blue);
	}
};


#pragma once
#include "gl_canvas2d.h"
#include "GameEvents.h"
#include "Tools.h"
#include "ColorDisplay.h"
#include "Botao.h"
#include "DrawableDisplay.h"
#include <functional>
#include <list>

class ToolBar : IRenderable
{
private :
	std::list<Button*> buttonList;
	DrawableDisplay* display;
	ColorDisplay* colorDisplay;

	Vector2 position;
	Vector2 size;

	Vector2 buttonSize;
	const int offset;

	MoveTool* moveTool;
	RotateTool* rotateTool;
	ScaleTool* scaleTool;
	FillTool* fillTool;

public :
	ToolBar(DrawableDisplay* display, Vector2 position, Vector2 size, int buttonOffset) : offset(buttonOffset)
	{
		this->position = position;
		this->size = size;
		this->display = display;
		buttonSize = Vector2(size.x - offset, (size.x / 2) - offset);
		SetToolButtons();

		EventManager::Instance()->AddListener<OnToolEvent>(ITool::OnTool);

		moveTool = new MoveTool();
		rotateTool = new RotateTool();
		scaleTool = new ScaleTool();
		fillTool = new FillTool();
		SetColorDisplay();
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

	GameLayer GetLayer() override
	{
		return GameLayer::UI;
	}

	void AddButton(std::function<void()> callback, Color color, const char label[])
	{
		int y = (buttonSize.y + offset) * buttonList.size() + offset;
		int x = position.x + offset;
		Button* b = new Button(Vector2(x, y), buttonSize, color, label, callback);
		buttonList.push_back(b);
	}

	void SetColorDisplay()
	{
		Vector2 pos;
		pos.x = offset;
		pos.y = (buttonSize.y + offset) * buttonList.size() + offset;
		colorDisplay = new ColorDisplay(pos, Vector2(buttonSize.x, size.y - pos.y - offset));
	}

	void SetToolButtons()
	{
		AddButton([this]() 
			{
				ITool::DisableAllTools();
				moveTool->AddToolListeners();
				display->SetState(false);
			}, Colors::orange, "Move");

		AddButton([this]() 
			{
				ITool::DisableAllTools();
				rotateTool->AddToolListeners();
				display->SetState(false);
			}, Colors::orange, "Rotate");

		AddButton([this]() 
			{
				ITool::DisableAllTools();
				scaleTool->AddToolListeners();
				display->SetState(false);
			}, Colors::orange, "Scale");

		AddButton([this]()
			{
				ITool::DisableAllTools();
				fillTool->AddToolListeners();
				display->SetState(false);
			}, Colors::orange, "Fill");

		AddButton([this]()
			{
				ITool::DisableAllTools();
				display->SetState(true);
			}, Colors::orange, "Draw");

		AddButton([this]()
			{
				ITool::DisableAllTools();
				display->SaveDisplay();
			}, Colors::orange, "Save");


	}
};
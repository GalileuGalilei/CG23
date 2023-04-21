#pragma once
#include "gl_canvas2d.h"
#include "GameEvents.h"
#include "Tools.h"
#include "ColorDisplay.h"
#include "Botao.h"
#include "DrawableDisplay.h"
#include <functional>
#include <list>


/// <summary>
/// Instancia todas as ferramentas e as adiciona na barra de ferramentas por meio de botões.
/// </summary>
class ToolBar : IRenderable
{
public:
	ToolBar(int screenWidth, int screenHeight, int barWidth, int buttonOffset);
	~ToolBar();

private :
	std::list<Button*> buttonList;
	ColorDisplay* colorDisplay;

	Vector2 position;
	Vector2 size;

	Vector2 buttonSize;
	const int offset;

	// ferramentas
	MoveTool* moveTool;
	RotateTool* rotateTool;
	ScaleTool* scaleTool;
	FillTool* fillTool;
	DeleteTool* deleteTool;
	SaveTool* saveTool;
	DrawTool* drawTool;

	// funções auxiliares
	void AddButton(std::function<void()> callback, Color color, const char label[]);
	void SetColorDisplay();
	void SetToolButtons();

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
};
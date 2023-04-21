#include "ToolBar.h"

ToolBar::ToolBar(int screenWidth, int screenHeight, int barWidth, int buttonOffset) : offset(buttonOffset)
{
	this->position = Vector2(0,0);
	this->size = Vector2(barWidth, screenHeight);
	buttonSize = Vector2(size.x - offset, (size.x / 2) - offset);
	SetToolButtons();

	EventManager::Instance()->AddListener<OnToolEvent>(ITool::OnTool);

	drawTool = new DrawTool(Vector2(barWidth + offset, 0), Vector2(screenWidth - barWidth, screenHeight));
	moveTool = new MoveTool();
	rotateTool = new RotateTool();
	scaleTool = new ScaleTool();
	fillTool = new FillTool();
	deleteTool = new DeleteTool();
	saveTool = new SaveTool();

	deleteTool->AddToolListeners();
	SetColorDisplay();
}

ToolBar::~ToolBar()
{
	for (Button* b : buttonList)
	{
		delete(b);
	}

	buttonList.clear();
}

void ToolBar::AddButton(std::function<void()> callback, Color color, const char label[])
{
	int y = (buttonSize.y + offset) * buttonList.size() + offset;
	int x = position.x + offset;
	Button* b = new Button(Vector2(x, y), buttonSize, color, label, callback);
	buttonList.push_back(b);
}

void ToolBar::SetColorDisplay()
{
	Vector2 pos;
	pos.x = offset;
	pos.y = (buttonSize.y + offset) * buttonList.size() + offset;
	colorDisplay = new ColorDisplay(pos, Vector2(buttonSize.x, size.y - pos.y - offset));
}

void ToolBar::SetToolButtons()
{
	AddButton([this]()
		{
			ITool::DisableAllTools();
			moveTool->AddToolListeners();
			deleteTool->AddToolListeners();
		}, Colors::orange, "Move");

	AddButton([this]()
		{
			ITool::DisableAllTools();
			rotateTool->AddToolListeners();
			deleteTool->AddToolListeners();
		}, Colors::orange, "Rotate");

	AddButton([this]()
		{
			ITool::DisableAllTools();
			scaleTool->AddToolListeners();
			deleteTool->AddToolListeners();
		}, Colors::orange, "Scale");

	AddButton([this]()
		{
			ITool::DisableAllTools();
			fillTool->AddToolListeners();
			deleteTool->AddToolListeners();
		}, Colors::orange, "Fill");

	AddButton([this]()
		{
			ITool::DisableAllTools();
			drawTool->AddToolListeners();
		}, Colors::orange, "Draw");

	AddButton([this]()
		{
			ITool::DisableAllTools();
			SaveTool::OnSaveTool(new OnToolEvent(NULL));
			deleteTool->AddToolListeners();
		}, Colors::orange, "Save");
}
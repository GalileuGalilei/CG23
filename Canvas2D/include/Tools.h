#pragma once
#include "EventManager.h"
#include "ColorDisplay.h"
#include "PolygonShape.h"

/// <summary>
/// Esse arquivo contem todas as classes que representam as ferramentas do programa assim como seus eventos.
/// </summary>

class OnToolEvent : public BaseEvent
{
public:

	PolygonShape* polygon;
	static EventType GetStaticType();

	EventType GetType() const override
	{
		return GetStaticType();
	}

	OnToolEvent(PolygonShape* polygon)
	{
		this->polygon = polygon;

	}
};

class ITool
{
private:
	static std::list<ITool*> toolList;

public:
	static void DisableAllTools()
	{
		for (ITool* tool : toolList)
		{
			tool->RemoveToolListeners();
		}
	}

	static void OnTool(BaseEvent* baseEvent)
	{
		OnToolEvent* args = (OnToolEvent*)baseEvent;
		selectedPolygon = args->polygon;
	}

protected:
	static PolygonShape* selectedPolygon;
	static std::list<PolygonShape*> polygonList;

	virtual void RemoveToolListeners() = 0;
	virtual void AddToolListeners() = 0;

	ITool()
	{
		toolList.push_back(this);
	}
};


class FillTool : public ITool
{
public:
	static Color selectedColor;
	static void OnFillTool(BaseEvent* baseEvent);
	ColorDisplay* display;

	void RemoveToolListeners() override
	{
		EventManager::Instance()->RemoveListener<OnClickEvent>(OnFillTool);
	}

	void AddToolListeners() override
	{
		EventManager::Instance()->AddListener<OnClickEvent>(OnFillTool);
	}
};

class MoveTool : public ITool
{
private:
	static bool isMoving;

public:
	static void OnMoveTool(BaseEvent* baseEvent);

	void RemoveToolListeners() override
	{
		EventManager::Instance()->RemoveListener<OnClickEvent>(OnMoveTool);
		EventManager::Instance()->RemoveListener<OnMouseOverEvent>(OnMoveTool);
	}

	void AddToolListeners() override
	{
		EventManager::Instance()->AddListener<OnClickEvent>(OnMoveTool);
		EventManager::Instance()->AddListener<OnMouseOverEvent>(OnMoveTool);
	}
};

class RotateTool : public ITool
{
private:
	static bool isRotating;

public:
	static void OnRotateTool(BaseEvent* baseEvent);

	void RemoveToolListeners() override
	{
		EventManager::Instance()->RemoveListener<OnClickEvent>(OnRotateTool);
		EventManager::Instance()->RemoveListener<OnMouseOverEvent>(OnRotateTool);
	}

	void AddToolListeners() override
	{
		EventManager::Instance()->AddListener<OnClickEvent>(OnRotateTool);
		EventManager::Instance()->AddListener<OnMouseOverEvent>(OnRotateTool);
	}
};

class ScaleTool : public ITool
{
private:
	static bool isScaling;

public:
	static void OnScaleTool(BaseEvent* baseEvent);

	void RemoveToolListeners() override
	{
		EventManager::Instance()->RemoveListener<OnClickEvent>(OnScaleTool);
		EventManager::Instance()->RemoveListener<OnMouseOverEvent>(OnScaleTool);
	}

	void AddToolListeners() override
	{
		EventManager::Instance()->AddListener<OnClickEvent>(OnScaleTool);
		EventManager::Instance()->AddListener<OnMouseOverEvent>(OnScaleTool);
	}
};


class DeleteTool : public ITool
{
public:
	static void OnDeleteTool(BaseEvent* baseEvent);
	
	void RemoveToolListeners() override
	{
		EventManager::Instance()->RemoveListener<OnKeyEvent>(OnDeleteTool);
	}
	
	void AddToolListeners() override
	{
		EventManager::Instance()->AddListener<OnKeyEvent>(OnDeleteTool);
	}
};

class SaveTool : public ITool
{
public:
	static void OnSaveTool(BaseEvent* baseEvent);
	static char savePath[];

	/// <summary>
	/// Quando a ferramenta é criada, já carrega os dados salvos
	/// </summary>
	SaveTool();

	//não há necesseidade de remover/adicionar listeners, pois essa ferramenta é usada apenas pelo botão
	void RemoveToolListeners() override{}
	void AddToolListeners() override {}
};
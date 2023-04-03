#pragma once
#include "EventManager.h"
class OnRenderEvent : BaseEvent
{
public:

	static EventType GetStaticType();
	OnRenderEvent() {};

	EventType GetType() const override
	{
		return GetStaticType();
	}

};

class IRenderable
{
public:
	static void RenderAll(BaseEvent* baseEvent);

private:
	static std::list<IRenderable*> renderList;
	virtual void OnRender(OnRenderEvent* args) const = 0;

protected:
	IRenderable()
	{
		renderList.push_back(this);
	}

	~IRenderable()
	{
		renderList.remove(this);
	}
};

class OnClickEvent : BaseEvent
{
public:

	static EventType GetStaticType();

	EventType GetType() const override
	{
		return GetStaticType();
	}

	int button, state, x, y;

	OnClickEvent(int button, int state, int x, int y)
	{
		this->button = button;
		this->state = state;
		this->x = x;
		this->y = y;
	}
};

class IClickable
{
private:
	static void ClickAll(BaseEvent* baseEvent);

public:
	static std::list<IClickable*> clickList;
	virtual void OnClick(OnClickEvent* args) const = 0;

protected:
	IClickable()
	{
		clickList.push_back(this);
	}

	~IClickable()
	{
		clickList.remove(this);
	}
};


#ifndef GAME_EVENTS
#define GAME_EVENTS

#include "EventManager.h"
#include "Vector2.h"

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
	virtual void OnRender(OnRenderEvent* args) = 0;

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

class OnMouseOverEvent : BaseEvent
{
private:
	static int oldX, oldY;

public:
	static EventType GetStaticType();

	EventType GetType() const override
	{
		return GetStaticType();
	}

	int x, y;
	Vector2 translation;

	OnMouseOverEvent(int x, int y)
	{
		this->x = x;
		this->y = y;

		translation = Vector2(x - oldX, y - oldY);
	}
};

class IClickable
{
private:
	virtual void OnClick(OnClickEvent* args) = 0;
	virtual void OnMouseOver(OnMouseOverEvent* args) = 0;

public:
	static std::list<IClickable*> clickList;
	static void ClickAll(BaseEvent* baseEvent);
	static void MouseOverAll(BaseEvent* baseEvent);

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

#endif // !GAME_EVENTS

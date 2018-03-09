#pragma once

struct EntityDeadEvent
{
	EntityId EntityId;
};

struct Contact
{
	EntityId EntityId;
};

struct CollisionBeginEvent
{
	Contact a;
	Contact b;
};

struct CollisionEndEvent
{
	Contact a;
	Contact b;
};


class EventHandler
{
public:

	template<typename E>
	void SendEvent(const E& event)
	{
		// TODO
	}
};

#pragma once

#include "Entity.h"

struct EntityDeadEvent
{
	Entity Entity;
};

struct Contact
{
	Entity Entity;
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

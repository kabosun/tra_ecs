#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <cassert>
#include "../ecs/Event.h"
#include "../ecs/System.h"
#include "../ecs/World.h"

class PhysicsSystem : public System<PhysicsSystem>
{

};

class LifetimeSystem : public System<LifetimeSystem>
{
public:

	void Update(DeltaFrame dt) override
	{
		for (LifetimeComponent& c : GetWorld()->GetRegistry<LifetimeComponent>()->Components)
		{
			if (c.current_lifetime >= 0)
			{
				GetWorld()->KillEntity(c.EntityId);
			}
			else
			{
				c.current_lifetime--;
			}
		}
	}
};

class ProjectileSystem : public System<ProjectileSystem>
{
public:

	void Update(DeltaFrame dt) override
	{
	}

	void OnCollisionBegin(CollisionBeginEvent& e)
	{

	}

	void OnCollisionEnd(CollisionBeginEvent& e)
	{
		GetWorld()->KillEntity(e.a.Entity);
	}
};

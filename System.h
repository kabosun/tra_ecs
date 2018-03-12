#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <cassert>
#include "ECS.h"
#include "Event.h"
#include "World.h"

class PhysicsSystem : public System<PhysicsSystem>
{

};

class LifetimeSystem : public System<LifetimeSystem>
{
public:
	WorldSystem* WorldSystem;
	
	LifetimeSystem()
	{
		WorldSystem = &WorldSystem::GetInstance();
	}

	void Update(DeltaFrame dt) override
	{
		assert(WorldSystem != nullptr);
		
		for (LifetimeComponent& c : WorldSystem->GetRegistry<LifetimeComponent>()->Components)
		{
			if (c.current_lifetime >= 0)
			{
				WorldSystem->KillEntity(c.EntityId);
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
	WorldSystem* WorldSystem;

	ProjectileSystem()
	{
		WorldSystem = &WorldSystem::GetInstance();
		
		// Add collision Callback Fuction.
	}

	void Update(DeltaFrame dt) override
	{
		assert(WorldSystem != nullptr);
	}

	void OnCollisionBegin(CollisionBeginEvent& e)
	{

	}

	void OnCollisionEnd(CollisionBeginEvent& e)
	{
		WorldSystem->KillEntity(e.a.EntityId);
	}
};

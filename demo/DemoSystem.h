#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <cassert>
#include "Event.h"
#include "System.h"
#include "World.h"
#include "DemoComponent.h"

class PhysicsSystem : public System<Requires<TransformComponent, PhysicsComponent>>
{
	double friction = 0.8f;

public:

	void Update(DeltaFrame dt) override
	{
		for (auto& entity : GetEntities())
		{
			TransformComponent* transform = entity.GetComponent<TransformComponent>();
			PhysicsComponent* physics = entity.GetComponent<PhysicsComponent>();

			transform->Position.X += physics->Velocity.X;
			transform->Position.Y += physics->Velocity.Y;

			physics->Velocity.X *= friction * dt;
			physics->Velocity.Y *= friction * dt;
		}
	}
};

class LifetimeSystem : public System<Requires<LifetimeComponent>>
{
public:

	void Update(DeltaFrame dt) override
	{
		for (auto& entity : GetEntities())
		{
			LifetimeComponent* lifetime = entity.GetComponent<LifetimeComponent>();

			if (lifetime->current_lifetime >= 0)
			{
				GetWorld().KillEntity(entity);
			}
			else
			{
				lifetime->current_lifetime--;
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
		GetWorld().KillEntity(e.a.Entity);
	}
};

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

namespace SystemType {
enum SystemType
{
	Physics = 1,
	Lifetime = 2,
	Projectile = 4,
};
}

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
			
			std::cout << "X:" << transform->Position.X << " Y:" << transform->Position.Y << std::endl;
		}
	}
};
template<> const SystemTypeId System<Requires<TransformComponent, PhysicsComponent>>::TypeId = SystemType::Physics;

class LifetimeSystem : public System<Requires<LifetimeComponent>>
{
public:

	void Update(DeltaFrame dt) override
	{
		for (auto& entity : GetEntities())
		{
			LifetimeComponent* lifetime = entity.GetComponent<LifetimeComponent>();

			if (lifetime->current_lifetime <= 0)
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
template<> const SystemTypeId System<Requires<LifetimeComponent>>::TypeId = SystemType::Lifetime;

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
template<> const SystemTypeId System<ProjectileSystem>::TypeId = SystemType::Projectile;


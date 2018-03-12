#pragma once

#include "ECS_Demo.h"
#include <iostream>
#include "../ecs/ECS.h"
#include "DemoComponent.h"
#include "DemoSystem.h"

void ECS_Demo()
{
	//auto TransformComponents = std::shared_ptr<ComponentRegistry<TransformComponent>>();

	World& world = World::GetInstance();

	// component setup.
	world.AddComponentRegistry<TransformComponent>();
	world.AddComponentRegistry<PhysicsComponent>();
	world.AddComponentRegistry<LifetimeComponent>();

	// system setup.
	PhysicsSystem physicsSystem;
	LifetimeSystem lifetimeSystem;
	ProjectileSystem projectileSystem;

	world.AddSystem(physicsSystem);
	world.AddSystem(lifetimeSystem);
	world.AddSystem(projectileSystem);

	auto count = world.ComponentRegistryMap.count(ComponentType::Lifetime);
	std::cout << count << std::endl;

	// create entity.
	Entity entity1 = world.CreateEntity();
	{
		entity1.AddComponent<TransformComponent>();
		entity1.AddComponent<PhysicsComponent>();
		entity1.AddComponent<LifetimeComponent>();
	}

	// world update.
	DeltaFrame dt = 1;
	{
		world.Refresh();

		physicsSystem.Update(dt);
		projectileSystem.Update(dt);
		lifetimeSystem.Update(dt);
	}

	std::cout << "ecs end." << std::endl;
}

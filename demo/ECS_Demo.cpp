#include "ECS_Demo.h"
#include <iostream>
#include "ECS.h"
#include "DemoComponent.h"
#include "DemoSystem.h"

void ECS_Demo()
{
	World& world = World::GetInstance();

	// component setup.
	world.AddComponentStorage<TransformComponent>();
	world.AddComponentStorage<PhysicsComponent>();
	world.AddComponentStorage<LifetimeComponent>();

	// system setup.
	PhysicsSystem physicsSystem;
	LifetimeSystem lifetimeSystem;
	ProjectileSystem projectileSystem;

	world.AddSystem(physicsSystem);
	world.AddSystem(lifetimeSystem);
	world.AddSystem(projectileSystem);

	// create entity.
	Entity& entity1 = world.CreateEntity();
	std::cout << "EntityId(1):" << entity1.Id << std::endl;
	{
		entity1.AddComponent<TransformComponent>();
		std::cout << "EntityId(2):" << entity1.Id << std::endl;

		entity1.AddComponent<PhysicsComponent>();
		entity1.AddComponent<LifetimeComponent>();
		
		auto&& physics = entity1.GetComponent<PhysicsComponent>();
		physics->Velocity.X = 1.5;
		physics->Velocity.Y = 0.5;
	}

	// world update.
	DeltaFrame dt = 1;
	
	for (int i = 0; i < 10; i++)
	{
		world.Refresh();

		physicsSystem.Update(dt);
		projectileSystem.Update(dt);
		lifetimeSystem.Update(dt);
	}

	std::cout << "ecs end." << std::endl;
}

#pragma once

#include "EntityRegistry.h"
#include "Event.h"
#include "Component.h"
#include "World.h"

void ECS()
{
	//auto TransformComponents = std::shared_ptr<ComponentRegistry<TransformComponent>>();

	WorldSystem& WorldSystem = WorldSystem::GetInstance();

	WorldSystem.AddComponentRegistry<TransformComponent>();
	WorldSystem.AddComponentRegistry<PhysicsComponent>();
	WorldSystem.AddComponentRegistry<LifetimeComponent>();

	WorldSystem.AddSystem<PhysicsSystem>();
	WorldSystem.AddSystem<LifetimeSystem>();
	WorldSystem.AddSystem<ProjectileSystem>();
	
	auto count = WorldSystem.ComponentRegistryMap.count(ComponentType::Lifetime);
	std::cout << count << std::endl;
	
	EntityId EntityId = WorldSystem.CreateEntity();
	{
		WorldSystem.AttachComponent<TransformComponent>(EntityId);
		WorldSystem.AttachComponent<PhysicsComponent>(EntityId);
	}

	DeltaFrame dt = 1;
	for (auto&& system : WorldSystem.Systems)
	{
		system->Update(dt);
	}
}

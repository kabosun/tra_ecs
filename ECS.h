#pragma once

#include "EntityRegistry.h"
#include "Event.h"
#include "Component.h"
#include "World.h"

void ECS()
{
	//auto TransformComponents = std::shared_ptr<ComponentRegistry<TransformComponent>>();

	WorldSystem WorldSystem;

	// �R���|�[�l���g�^�C�v��o�^����
	WorldSystem.AddComponentRegistry<TransformComponent>();
	WorldSystem.AddComponentRegistry<PhysicsComponent>();
	WorldSystem.AddComponentRegistry<LifetimeComponent>();

	// �V�X�e����o�^����
	WorldSystem.AddSystem<PhysicsSystem>();
	WorldSystem.AddSystem<LifetimeSystem>();
	WorldSystem.AddSystem<ProjectileSystem>();

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

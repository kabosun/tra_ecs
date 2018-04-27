#pragma once

/**
 * 便利関数
 */
#include "ECS2.h"

using namespace ecs2;

class EntityFacade final
{
	Entity entity;
	ComponentSystemRegistry* componentSystemRegistry;

public:
	EntityFacade(ComponentSystemRegistry* componentSystemRegistry, Entity entity)
	{
		this->entity = entity;
		this->componentSystemRegistry = componentSystemRegistry;
	}

	TransformFacade Transform()
	{
		auto&& component = componentSystemRegistry->Get<TransformComponentSystem>();
		return TransformFacade(entity, component.get());
	}

	PhysicsFacade Physics()
	{
		auto&& component = componentSystemRegistry->Get<SumoPhysicsComponentSystem>();
		return PhysicsFacade(entity, component.get());
	}

	HealthFacade Health()
	{
		auto&& component = componentSystemRegistry->Get<HealthComponentSystem>();
		return HealthFacade(entity, component.get());
	}
};

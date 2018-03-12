#pragma once

#include "DemoComponent.h"

enum class ComponentDepends
{
	RigidBody = ComponentType::Transform | ComponentType::Physics,
	Lifetime = ComponentType::Lifetime,
	Projectile = RigidBody | Lifetime,
	ProjectileSpawner = ComponentType::ProjectileSpawner,
	Fighter = RigidBody | ProjectileSpawner | ComponentType::Skill,
};

#pragma once

#include "../ecs/Entity.h"

enum ComponentType
{
	Transform = 1,
	Physics = 2,
	Lifetime = 4,
	Projectile = 8,
	ProjectileSpawner = 16,
	Skill = 32,
};

template<typename T>
struct Vector2
{
	T X;
	T Y;
};
using Vector2f = Vector2<double>;

struct TransformComponent : public Component<TransformComponent>
{
	Vector2f Position;
	Vector2f Rotation;
};
template<> const ComponentTypeId Component<TransformComponent>::TypeId = ComponentType::Transform;


struct PhysicsComponent : public Component<PhysicsComponent>
{
	// TODO Shape

	Vector2f Velocity;
	float Weight;
};
template<> const ComponentTypeId Component<PhysicsComponent>::TypeId = ComponentType::Physics;


struct LifetimeComponent : public Component<LifetimeComponent>
{
	int max_lifetime;
	int current_lifetime;
};
template<> const ComponentTypeId Component<LifetimeComponent>::TypeId = ComponentType::Lifetime;

struct ProjectileComponent : public Component<ProjectileComponent>
{
	int max_lifetime;
	int current_lifetime;
};
template<> const ComponentTypeId Component<ProjectileComponent>::TypeId = ComponentType::Projectile;

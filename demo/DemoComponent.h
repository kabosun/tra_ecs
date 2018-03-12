#pragma once

#include "../ecs/Entity.h"

enum ComponentType
{
	Transform = 1,
	Physics = 2,
	Lifetime = 4,
	ProjectileSpawner = 8,
	Skill = 16,
};

template<typename T>
struct Vector2
{
	T x;
	T y;
};
using Vector2f = Vector2<float>;

struct TransformComponent : public Component<TransformComponent>
{
	Vector2f Position;
	Vector2f Rotation;
};
template<> const ComponentTypeId Component<TransformComponent>::COMPONENT_TYPE = ComponentType::Transform;


struct PhysicsComponent : public Component<PhysicsComponent>
{
	// TODO Shape

	Vector2f Velocity;
	float Weight;
};
template<> const ComponentTypeId Component<PhysicsComponent>::COMPONENT_TYPE = ComponentType::Physics;


struct LifetimeComponent : public Component<LifetimeComponent>
{
	int max_lifetime;
	int current_lifetime;
};
template<> const ComponentTypeId Component<LifetimeComponent>::COMPONENT_TYPE = ComponentType::Lifetime;

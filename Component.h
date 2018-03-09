#pragma once

enum ComponentType
{
	Transform = 1,
	Physics = 2,
	Lifetime = 4,
	ProjectileSpawner = 8,
	Skill = 16,
};

struct TransformComponent : public Component<TransformComponent>
{
	FFixFloatVector2 Position;
	FFixFloatVector2 Rotation;
};
const ComponentTypeId Component<TransformComponent>::COMPONENT_TYPE = ComponentType::Transform;


struct PhysicsComponent : public Component<PhysicsComponent>
{
	// TODO Shape

	FFixFloatVector2 Velocity;
	FFixFloat Weight;
};
const ComponentTypeId Component<PhysicsComponent>::COMPONENT_TYPE = ComponentType::Physics;


struct LifetimeComponent : public Component<LifetimeComponent>
{
	int max_lifetime;
	int current_lifetime;
};
const ComponentTypeId Component<LifetimeComponent>::COMPONENT_TYPE = ComponentType::Lifetime;

#pragma once

using EntityId = unsigned int;
using SystemTypeId = unsigned int;
using ComponentTypeId = unsigned int;
using DeltaFrame = int;

class IComponent
{};

class Entity
{
public:

	EntityId Id;

	Entity(EntityId Id)
	{
		this->Id = Id;
	}

	virtual ~Entity()
	{}

	template<typename T>
	void AddComponent()
	{
		AddComponent(*this, T::COMPONENT_TYPE);
	}

	void Kill();

private:
	void AddComponent(Entity& entity, ComponentTypeId type);
};

template<typename T>
class Component : public IComponent
{
public:
	static const ComponentTypeId COMPONENT_TYPE;

	EntityId EntityId;

	Component()
	{
	}
};
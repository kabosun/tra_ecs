#pragma once

using DeltaFrame = float;
using EntityId = unsigned int;
using ComponentTypeId = unsigned int;
using SystemTypeId = unsigned int;

class World;
class IComponent;
class IComoponentStorage;

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
		AddComponent(*this, T::TypeId);
	}

	template<typename T>
	T* GetComponent() const
	{
		return static_cast<T*>(GetComponent(T::TypeId));
	}

	void Kill();

private:
	void AddComponent(const Entity& entity, ComponentTypeId type);

	IComponent* GetComponent(ComponentTypeId type) const;
};

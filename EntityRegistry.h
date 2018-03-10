#pragma once

#include "Entity.h"
#include <vector>
#include <memory>

using DeltaFrame = int;

class EntityRegistry
{
	EntityId EntityIdCoutner = 0;

public:
	std::vector<EntityId> Entities;

	EntityId CreateEntity()
	{
		EntityIdCoutner++;
		return EntityIdCoutner;
	}
};

class IComponentRegistry
{
public:
	virtual void CreateComponent(const EntityId id) {}
};

template<typename T>
class ComponentRegistry : public IComponentRegistry
{
public:
	std::vector<T> Components;

	T* GetComponent(const EntityId id)
	{
		for (auto&& a : Components)
		{
			if (a.EntityId == id) return &a;
		}
		return nullptr;
	}

	virtual void CreateComponent(const EntityId id) override
	{
		T c;
		c.EntityId = id;
		Components.push_back(c);
	}
};

class ISystem
{
public:
	virtual void Update(DeltaFrame dt) {}
};

template<typename T>
class System : public ISystem
{
protected:
	std::shared_ptr<ComponentRegistry<T>> registry;

public:

	virtual ~System() {}
};

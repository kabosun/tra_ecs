#pragma once

#include <vector>
#include <memory>
#include "Entity.h"

class EntityRegistry
{
	EntityId EntityIdCoutner = 0;
	std::vector<Entity> Entities;

public:

	Entity& CreateEntity()
	{
		EntityIdCoutner++;

		//auto e = Entity(EntityIdCoutner);
		Entities.emplace_back(EntityIdCoutner);

		return Entities.back();
	}

	void Add(const Entity& entity)
	{
		Entities.push_back(entity);
	}

	const std::vector<Entity> GetEntities() const
	{
		return Entities;
	}
};

class IComponentRegistry
{
public:
	virtual void CreateComponent(const Entity entity) {}
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

	virtual void CreateComponent(const Entity entity) override
	{
		T c;
		c.EntityId = entity.Id;
		Components.push_back(c);
	}
};

#pragma once

#include <vector>
#include <memory>
#include "Component.h"

class IComponentStorage
{
public:
	virtual ~IComponentStorage()
	{}
	
	virtual void CreateComponent(const Entity& entity) {}

	virtual IComponent* GetComponent(const Entity& entity) = 0;

	virtual void RemoveComponent(const Entity& entity) = 0;
};

template<typename T>
class ComponentStorage : public IComponentStorage
{
	std::vector<T> Components;

public:
	virtual void CreateComponent(const Entity& entity) override
	{
		T c;
		c.EntityId = entity.Id;
		Components.push_back(c);
	}

	virtual IComponent* GetComponent(const Entity& entity) override
	{
		for (auto&& component : Components)
		{
			if (component.EntityId == entity.Id) return &component;
		}
		return nullptr;
	}

	virtual void RemoveComponent(const Entity& entity) override
	{
		for (auto&& component : Components)
		{
			if (component.EntityId == entity.Id)
			{
				size_t index = &component - &Components[0];
				Components[index] = Components.back();
				Components.pop_back();
				return;
			}
		}
	}
};

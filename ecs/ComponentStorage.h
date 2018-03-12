#pragma once

#include <vector>
#include <memory>
#include "Component.h"

class IComponentStorage
{
public:
	virtual void CreateComponent(const Entity entity) {}

	virtual IComponent* GetComponent(const Entity entity) = 0;
};

template<typename T>
class ComponentStorage : public IComponentStorage
{
	std::vector<T> Components;

public:
	virtual void CreateComponent(const Entity entity) override
	{
		T c;
		c.EntityId = entity.Id;
		Components.push_back(c);
	}

	virtual IComponent* GetComponent(const Entity entity) override
	{
		for (auto&& component : Components)
		{
			if (component.EntityId == entity.Id) return &component;
		}
		return nullptr;
	}
};

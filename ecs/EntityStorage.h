#pragma once

#include <vector>
#include <memory>
#include "Entity.h"

class EntityStorage
{
	EntityId EntityIdCoutner = 0;
	std::vector<Entity> Entities;

public:

	Entity& CreateEntity()
	{
		EntityIdCoutner++;

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

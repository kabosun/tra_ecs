#pragma once

#include <vector>
#include "Entity.h"

class World;

class ISystem
{
	World* m_World;
	std::vector<Entity> m_Entities;

public:
	virtual void Init() {}
	virtual void Update(DeltaFrame dt) {}

	void SetWorld(World* world)
	{
		m_World = world;
	}

	World* GetWorld() const
	{
		return m_World;
	}

	const std::vector<Entity>& GetEntities() const
	{
		return m_Entities;
	}

	void Add(const Entity& entity)
	{
		m_Entities.push_back(entity);
	}
};

template<typename T>
class System : public ISystem
{
protected:
	std::shared_ptr<ComponentRegistry<T>> registry;

public:

	virtual ~System() {}
};

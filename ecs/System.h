#pragma once

#include <vector>
#include "Entity.h"
#include "Filter.h"

class World;

class ISystem
{
	Filter m_Filter;
	World* m_World;
	std::vector<Entity> m_Entities;

public:

	ISystem(Filter& filter)
		: m_World(nullptr)
		, m_Filter(filter)
	{}

	virtual ~ISystem()
	{}

	virtual void Init() {}
	virtual void Update(DeltaFrame dt) {}

	const Filter& GetFilter() const
	{
		return m_Filter;
	}

	void SetWorld(World* world)
	{
		m_World = world;
	}

	World& GetWorld() const
	{
		return *m_World;
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

template<class Requires>
class System : public ISystem
{
public:
	System()
		: ISystem{ MakeFilter<Requires>() }
	{}
};

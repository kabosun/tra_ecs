#pragma once

#include <vector>
#include "Entity.h"
#include "Filter.h"

class World;

class ISystem
{
	Filter m_Filter;
	World* m_World;

	// エンティティのリスト。順番は要素削除のたびに入れ替わるので保たれない。
	std::vector<Entity> m_Entities;

public:
	
	ISystem()
	{}
	
	ISystem(Filter filter)
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

	void Remove(const Entity& entity)
	{
		size_t index = &entity - &m_Entities[0];
		m_Entities[index] = m_Entities.back();
		m_Entities.pop_back();
	}
};

template<class Requires>
class System : public ISystem
{
public:
	static const SystemTypeId TypeId;
	
	System()
		: ISystem(MakeFilter<Requires>())
	{}
};

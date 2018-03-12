#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <cassert>
#include "Event.h"
#include "EntityRegistry.h"
#include "System.h"

class World
{
	std::map<SystemTypeId, ISystem*> m_Systems;
	EventHandler* EventHandler;
	EntityRegistry m_AliveEntities;
	EntityRegistry m_KilledEntities;
	
	World()
	{}
	
public:
	std::map<ComponentTypeId, IComponentRegistry*> ComponentRegistryMap;

public:
	
	static World& GetInstance()
	{
		static World Instance;
		return Instance;
	}

	virtual ~World()
	{
		for (auto pair : ComponentRegistryMap)
		{
			delete pair.second;
		}
	}

	template<typename T>
	ComponentRegistry<T>* GetRegistry()
	{
		assert(ComponentRegistryMap.count(T::COMPONENT_TYPE) != 0);
		
		auto&& m = ComponentRegistryMap.at(T::COMPONENT_TYPE);
		return dynamic_cast<ComponentRegistry<T>*>(m);
	}

	void KillEntity(const Entity entity)
	{
		//EntityDeadEvent e = { entity };
		//EventHandler->SendEvent<EntityDeadEvent>(e);

		m_KilledEntities.Add(entity);
	}

	template<typename T>
	void AddComponentRegistry()
	{
		IComponentRegistry* registry = new ComponentRegistry<T>();

		ComponentRegistryMap.insert(std::make_pair(T::COMPONENT_TYPE, registry));
	}

	template<class TSystem>
	void AddSystem(TSystem& system)
	{
		system.SetWorld(this);
		system.Init();
	}

	Entity& CreateEntity()
	{
		return m_AliveEntities.CreateEntity();
	}

	void AttachComponent(Entity& Entity, ComponentTypeId Type)
	{
		auto&& registry = ComponentRegistryMap.at(Type);

		assert(registry != nullptr);

		registry->CreateComponent(Entity);
		
	}

	void Refresh()
	{
		// systemにentityを登録する
		for (const Entity& entity : m_AliveEntities.GetEntities())
		{
			for (auto&& pair : m_Systems)
			{
				// TODO filter
				pair.second->Add(entity);
			}
		}
	}
};

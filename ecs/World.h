#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <cassert>
#include "Event.h"
#include "EntityStorage.h"
#include "ComponentStorage.h"
#include "System.h"

class World
{
	std::map<SystemTypeId, ISystem*> m_Systems;
	EventHandler* EventHandler;
	EntityStorage m_AliveEntities;
	EntityStorage m_KilledEntities;
	
	World()
	{}
	
public:
	std::map<ComponentTypeId, IComponentStorage*> ComponentStorageMap;

public:
	
	static World& GetInstance()
	{
		static World Instance;
		return Instance;
	}

	virtual ~World()
	{
		for (auto pair : ComponentStorageMap)
		{
			delete pair.second;
		}
	}

	IComponentStorage* GetStorage(ComponentTypeId type)
	{
		assert(ComponentStorageMap.count(type) != 0);
		
		return ComponentStorageMap.at(type);
	}

	void KillEntity(const Entity entity)
	{
		//EntityDeadEvent e = { entity };
		//EventHandler->SendEvent<EntityDeadEvent>(e);

		m_KilledEntities.Add(entity);
	}

	template<typename T>
	void AddComponentStorage()
	{
		auto&& registry = new ComponentStorage<T>();

		ComponentStorageMap.insert(std::make_pair(T::TypeId, registry));
	}

	template<typename T>
	void AddSystem(T& system)
	{
		system.SetWorld(this);
		system.Init();
		
		m_Systems[T::TypeId] = &system;
	}

	Entity& CreateEntity()
	{
		return m_AliveEntities.CreateEntity();
	}

	void AttachComponent(const Entity& Entity, ComponentTypeId Type)
	{
		auto&& registry = ComponentStorageMap.at(Type);

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
				// TODO 登録するsystemはfilterで区別する
				pair.second->Add(entity);
			}
		}
	}
};

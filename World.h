#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <cassert>
#include "ECS.h"
#include "Event.h"

class WorldSystem
{
	EventHandler* EventHandler;
	EntityRegistry EntityRegistry;
	
	WorldSystem()
	{
	}
	
public:
	std::map<ComponentTypeId, IComponentRegistry*> ComponentRegistryMap;

public:
	
	static WorldSystem& GetInstance()
	{
		static WorldSystem Instance;
		return Instance;
	}

	virtual ~WorldSystem()
	{
		for (auto pair : ComponentRegistryMap)
		{
			delete pair.second;
		}
	}

	std::vector<std::shared_ptr<ISystem>> Systems;

	template<typename T>
	ComponentRegistry<T>* GetRegistry()
	{
		assert(ComponentRegistryMap.count(T::COMPONENT_TYPE) != 0);
		
		auto&& m = ComponentRegistryMap.at(T::COMPONENT_TYPE);
		return dynamic_cast<ComponentRegistry<T>*>(m);
	}

	void KillEntity(const EntityId id)
	{
		EntityDeadEvent e = { id };
		EventHandler->SendEvent<EntityDeadEvent>(e);
	}

	template<typename T>
	void AddComponentRegistry()
	{
		IComponentRegistry* registry = new ComponentRegistry<T>();

		ComponentRegistryMap.insert(std::make_pair(T::COMPONENT_TYPE, registry));
	}

	template<typename T>
	void AddSystem()
	{
		T* system = new T();
		Systems.push_back(std::shared_ptr<ISystem>(system));
	}

	EntityId CreateEntity()
	{
		return EntityRegistry.CreateEntity();
	}

	template<typename T>
	void AttachComponent(EntityId EntityId)
	{
		auto&& registry = ComponentRegistryMap.at(T::COMPONENT_TYPE);

		registry->CreateComponent(EntityId);
		
	}
};

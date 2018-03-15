#pragma once

#include <vector>
#include <memory>
#include <map>
#include <typeindex>
#include "ComponentSystem.h"

namespace ecs2
{
	class EntityRegistry;

	class ComponentSystemRegistry
	{
		std::shared_ptr<EntityRegistry> m_EntityRegistry;
		std::map<std::type_index, std::shared_ptr<IGarbageCollectable>> m_ComponentSystems;
		std::vector<std::shared_ptr<IUpdatable>> m_UpdatableSystems;
		
	public:
		ComponentSystemRegistry(std::shared_ptr<EntityRegistry> registry)
		{
			m_EntityRegistry = registry;
		}
		
		template<typename T>
		std::shared_ptr<T> Add()
		{
			auto p = std::make_shared<T>();
			p->m_CSRegistry = this;
			m_ComponentSystems[typeid(T)] = p;
			
			return p;
		}
		
		template<typename T>
		std::shared_ptr<T> AddUpdatable()
		{
			auto p = std::make_shared<T>();
			p->m_CSRegistry = this;
			m_ComponentSystems[typeid(T)] = p;
			m_UpdatableSystems.push_back(p);
			
			return p;
		}
		
		template<typename T>
		std::shared_ptr<T> Get()
		{
			return std::static_pointer_cast<T>(m_ComponentSystems[typeid(T)]);
		}
		
		void Update(float dt)
		{
			EntityRegistry* r = m_EntityRegistry.get();
			for (auto&& system : m_UpdatableSystems)
			{
				system->Update(r, dt);
			}
		}
		
		void GC()
		{
			EntityRegistry* r = m_EntityRegistry.get();
			for (auto pair : m_ComponentSystems)
			{
				pair.second->GC(r);
			}
		}
	};
	
}

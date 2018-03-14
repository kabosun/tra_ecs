#pragma once

#include <vector>
#include <deque>
#include <iostream>
#include "Entity.h"

namespace ecs2
{
	
	static const int MINIMUM_FREE_INDICES = 32;

	class IEntityEventListener
	{
	public:
		virtual void OnCreateEntity(Entity entity) = 0;
		virtual void OnRemoveEntity(Entity entity) = 0;
	};

	class EntityEvent
	{
		std::vector<IEntityEventListener*> m_EventListener;
	public:

		void AddListener(IEntityEventListener* listener)
		{
			m_EventListener.push_back(listener);
		}

		void RemoveListener(IEntityEventListener* listener)
		{
			//m_EventListener.erase();
		}

		void SendCreateEntityEvent(Entity e)
		{
			for (auto&& listener : m_EventListener)
			{
				listener->OnCreateEntity(e);
			}
		}


		void SendRemoveEntityEvent(Entity e)
		{
			for (auto&& listener : m_EventListener)
			{
				listener->OnRemoveEntity(e);
			}
		}
	};

	class EntityRegistry : public EntityEvent
	{
		std::vector<char> m_Generation;
		std::deque<int> m_Free;
		
	public:
		Entity Create()
		{
			int index = 0;
			
			if (m_Free.size() > MINIMUM_FREE_INDICES)
			{
				index = m_Free.front();
				m_Free.pop_front();
			}
			else
			{
				m_Generation.push_back(0);
				index = static_cast<int>(m_Generation.size() - 1);
			}
			
			Entity entity = Entity::Make(index, m_Generation[index]);

			SendCreateEntityEvent(entity);

			return entity;
		}
		
		bool Alive(Entity entity) const
		{
			const int index = entity.Index();
			return m_Generation[index] == entity.Generation();
		}
		
		void Remove(Entity entity)
		{
			if (Alive(entity))
			{
				const int index = entity.Index();
				++m_Generation[index];
				m_Free.push_back(index);

				SendRemoveEntityEvent(entity);
				
				std::cout << "Destory Entity " << index << std::endl;
			}
		}
	};

}

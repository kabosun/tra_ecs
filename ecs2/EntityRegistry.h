#pragma once

#include <vector>
#include <deque>
#include "Entity.h"

namespace ecs2
{
	
	static const int MINIMUM_FREE_INDICES = 32;

	class EntityRegistry
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
			
			return Entity::Make(index, m_Generation[index]);
		}
		
		bool Alive(Entity entity) const
		{
			auto i = entity.Index();
			return m_Generation[i] == entity.Generation();
		}
		
		void Destroy(Entity entity)
		{
			if (Alive(entity))
			{
				const int index = entity.Index();
				++m_Generation[index];
				m_Free.push_back(index);
				
				std::cout << "Destory Entity " << index << std::endl;
			}
		}
	};

}

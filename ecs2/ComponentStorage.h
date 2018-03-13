#pragma once

#include <array>
#include <unordered_map>
#include <random>
#include "Entity.h"
#include "EntityRegistry.h"

namespace ecs2
{
	std::random_device rand;
	std::mt19937 mt;
	
	void Initialize()
	{
		mt.seed(rand());
	}
	
	template<typename T>
	struct Vector2
	{
		T X;
		T Y;
		
		Vector2()
		: X(0), Y(0)
		{}
	};
	using Vector2f = Vector2<float>;
	
	// lookup
	struct ComponentHandle
	{
		int index;
	};
	
	template<typename T>
	class ComponentStorage
	{
	protected:
		T m_Data;
		std::unordered_map<EntityId, int> m_LUTable;
		
		// entityを登録した時にcomponentを初期化する
		virtual void Reset(int index) = 0;
		
		// GCが実行されたときにcomponentを再配置する
		virtual void Compact(int index, int lastIndex) = 0;
		
	public:
		
		int Size() const
		{
			return m_Data.size;
		}
		
		ComponentHandle Lookup(Entity entity)
		{
			ComponentHandle h = {m_LUTable[entity.Id]};
			return h;
		}
		
		int Create(Entity entity)
		{
			if (m_LUTable.count(entity.Id) == 0)
			{
				auto n = m_Data.size;
				m_Data.entity[n] = entity;
				m_LUTable[entity.Id] = n;
				++m_Data.size;
				Reset(n);
				return n;
			}
			else
			{
				auto n = m_LUTable[entity.Id];
				Reset(n);
				return n;
			}
		}
		
		void Destroy(int index)
		{
			int lastIndex = m_Data.size - 1;
			Entity entity = m_Data.entity[index];
			Entity lastEntity = m_Data.entity[lastIndex];
			
			// 削除したentityの位置に最後のコンポーネントをコピーする
			m_Data.entity[index] = m_Data.entity[lastIndex];
			Compact(index, lastIndex);
			
			m_LUTable[lastEntity.Id] = index;
			m_LUTable.erase(entity.Id);
			
			--m_Data.size;
		}
		
		virtual void Update(EntityRegistry& registry, float dt) = 0;
		
		void GC(EntityRegistry& registry)
		{
			int alive_in_row = 0;
			
			while (m_Data.size > 0 && alive_in_row < 4)
			{
				int n = mt() % m_Data.size;
				if (registry.Alive(m_Data.entity[n]))
				{
					++alive_in_row;
					continue;
				}
				
				alive_in_row = 0;
				
				// entityが死んでいたらコンポーネントも削除する
				Destroy(n);
			}
		}
	};
}

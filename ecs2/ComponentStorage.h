#pragma once

#include <array>
#include <unordered_map>
#include <random>
#include "Entity.h"
#include "EntityRegistry.h"

namespace ecs2
{
	static std::random_device rand;
	static std::mt19937 mt;
	
	static void Initialize()
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

	template<typename T>
	struct MaxValue
	{
		float Current;
		float Max;
	};

	
	// lookup
	struct ComponentHandle
	{
		int index;
	};

	class IUpdatable
	{
	public:
		virtual void Update(EntityRegistry& registry, float dt) = 0;
	};

	class IGarbageCollectable
	{
	public:
		virtual void GC(EntityRegistry& registry) = 0;
	};
	
	template<typename T>
	class ComponentStorage : public IGarbageCollectable
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
			return m_Data.Size;
		}
		
		ComponentHandle GetHandle(Entity entity)
		{
			ComponentHandle h = {m_LUTable[entity.Id]};
			return h;
		}
		
		int Create(Entity entity)
		{
			if (m_LUTable.count(entity.Id) == 0)
			{
				auto n = m_Data.Size;
				m_Data.Entity[n] = entity;
				m_LUTable[entity.Id] = n;
				++m_Data.Size;
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
		
		void Remove(int index)
		{
			int lastIndex = m_Data.Size - 1;
			Entity entity = m_Data.Entity[index];
			Entity lastEntity = m_Data.Entity[lastIndex];
			
			// 削除したentityの位置に最後のコンポーネントをコピーする
			m_Data.Entity[index] = m_Data.Entity[lastIndex];
			Compact(index, lastIndex);
			
			m_LUTable[lastEntity.Id] = index;
			m_LUTable.erase(entity.Id);
			
			--m_Data.Size;
		}
		
		void GC(EntityRegistry& registry)
		{
			int alive_in_row = 0;
			
			while (m_Data.Size > 0 && alive_in_row < 4)
			{
				int n = mt() % m_Data.Size;
				if (registry.Alive(m_Data.Entity[n]))
				{
					++alive_in_row;
					continue;
				}
				
				alive_in_row = 0;
				
				// entityが死んでいたらコンポーネントも削除する
				Remove(n);
			}
		}
	};
}

#pragma once

#include <vector>
#include <unordered_map>
#include "Entity.h"
#include "EntityRegistry.h"

namespace ecs2
{
	class ComponentRegistry;
	
	struct ComponentHandle
	{
		int index;

		bool IsValid() const
		{
			return index != -1;
		}
	};

	class IUpdatable
	{
	public:
		virtual void Update(EntityRegistry& registry, float dt) = 0;
	};

	class IComponent
	{
	public:
		virtual void GC(const EntityRegistry& registry) = 0;
	};
	
	class Component : public IComponent
	{
		friend ComponentRegistry;
		
		ComponentRegistry* m_ComponentRegistry;
		int m_Size = 0;
		std::vector<Entity> m_Entity;

	protected:
		std::unordered_map<EntityId, int> m_LUTable;
		
		// entityを登録した時にcomponentを初期化する
		virtual void Reset(int index) = 0;
		
		// GCが実行されたときにcomponentを再配置する
		virtual void Compact(int index, int lastIndex) = 0;

		virtual void OnCreate(int index)
		{}

		virtual void OnRemove(int index)
		{}
		
		ComponentRegistry* ComponentRegistry()
		{
			return m_ComponentRegistry;
		}
		
	public:
		virtual ~Component()
		{}
		
		virtual void Initialize(EntityRegistry& registry, int maxSize)
		{
			m_Entity.resize(maxSize);
		}
		
		int Size() const
		{
			return m_Size;
		}
		
		inline Entity GetEntity(int index) const
		{
			return m_Entity[index];
		}
		
		ComponentHandle GetHandle(Entity entity)
		{
			ComponentHandle h = {m_LUTable[entity.Id]};
			return h;
		}
		
		ComponentHandle Attach(Entity entity)
		{
			if (m_LUTable.count(entity.Id) == 0)
			{
				auto n = m_Size;
				m_Entity[n] = entity;
				m_LUTable[entity.Id] = n;
				++m_Size;
				Reset(n);

				OnCreate(n);
				
				ComponentHandle h = { n };
				return h;
			}
			else
			{
				auto n = m_LUTable[entity.Id];
				Reset(n);

				OnCreate(n);

				ComponentHandle h = { m_LUTable[entity.Id] };
				return h;
			}
		}
		
		void GC(const EntityRegistry& registry) override
		{
			int alive_in_row = 0;
			
			while (m_Size > 0 && alive_in_row < 4)
			{
				int n = mt() % m_Size;
				if (registry.Alive(m_Entity[n]))
				{
					++alive_in_row;
					continue;
				}
				
				alive_in_row = 0;
				
				// entityが死んでいたらコンポーネントも削除する
				Remove(n);
			}
		}
		
	private:
		// GCされたコンポーネントを削除します
		void Remove(int index)
		{
			OnRemove(index);

			int lastIndex = m_Size - 1;
			Entity entity = m_Entity[index];
			Entity lastEntity = m_Entity[lastIndex];
			
			// 削除したentityの位置に最後のコンポーネントをコピーする
			m_Entity[index] = m_Entity[lastIndex];
			Compact(index, lastIndex);
			
			m_LUTable[lastEntity.Id] = index;
			m_LUTable.erase(entity.Id);
			
			--m_Size;
		}
	};

}

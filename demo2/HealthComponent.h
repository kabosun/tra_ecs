#pragma once

#include <array>
#include "../ecs2/Entity.h"
#include "../ecs2/ComponentSystem.h"

namespace ecs2
{
	using Health = MaxValue<int>;

	// コンポーネント
	struct HealthComponent
	{
		static const int MAX_COMPONENT = 128;
		
		// 必須
		int Size = 0;
		std::array<Entity, MAX_COMPONENT> Entity;
		
		// ユーザー定義
		std::array<Health, MAX_COMPONENT> Health;
	};
	
	class HealthComponentSystem : public ComponentSystem<HealthComponent>, public IUpdatable
	{
	public:
		Health GetHealth(ComponentHandle handle) const
		{
			return m_Data.Health[handle.index];
		}

		void SetHealth(ComponentHandle handle, const Health& health)
		{
			m_Data.Health[handle.index] = health;
		}
		
		void Update(EntityRegistry* eRegistry, float dt) override
		{
			for (int i=0; i<m_Data.Size; i++)
			{
				Health& health = m_Data.Health[i];
				if (health.Current <= 0)
				{
					// Destory Entity
					eRegistry->Remove(m_Data.Entity[i]);
				}
			}
		}
		
	protected:
		void Reset(int index) override
		{
			m_Data.Health[index].Current = 10;
			m_Data.Health[index].Max = 10;
		}
		
		void Compact(int index, int lastIndex) override
		{
			m_Data.Health[index] = m_Data.Health[lastIndex];
		}
	};
	
	class HealthFacade
	{
		HealthComponentSystem* component;
		Entity entity;
	public:
		static HealthFacade Create(Entity entity, HealthComponentSystem* component)
		{
			HealthFacade facade;
			facade.entity = entity;
			facade.component = component;
			
			return facade;
		}
		
		Health GetHealth() const
		{
			ComponentHandle handle = component->GetHandle(entity);
			return component->GetHealth(handle);
		}
		
		void SetHealth(const Health& health)
		{
			ComponentHandle handle = component->GetHandle(entity);
			component->SetHealth(handle, health);
		}
	};
}


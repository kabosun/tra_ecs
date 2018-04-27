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

	class HealthFacade final
	{
		HealthComponentSystem* component;
		ComponentHandle handle;

	public:
		HealthFacade(Entity entity, HealthComponentSystem* component)
		{
			this->component = component;
			this->handle = component->GetHandle(entity);
		}

		Health GetHealth() const
		{
			return component->GetHealth(handle);
		}

		HealthFacade& SetHealth(const Health& health)
		{
			component->SetHealth(handle, health);
			return *this;
		}
	};
}


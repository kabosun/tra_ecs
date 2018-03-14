#pragma once

#include <array>
#include "../ecs2/Entity.h"
#include "../ecs2/ComponentSystem.h"

namespace ecs2
{
	using Lifetime = MaxValue<int>;
	
	// コンポーネント
	struct LifetimeComponent
	{
		static const int MAX_COMPONENT = 128;
		
		// 必須
		int Size = 0;
		std::array<Entity, MAX_COMPONENT> Entity;
		
		// ユーザー定義
		std::array<Lifetime, MAX_COMPONENT> Lifetime;
	};
	
	class LifetimeComponentSystem : public ComponentSystem<LifetimeComponent>, public IUpdatable
	{
	public:
		Lifetime& GetLifetime(ComponentHandle handle)
		{
			return m_Data.Lifetime[handle.index];
		}
		
		void Update(EntityRegistry& registry, float dt) override
		{
			for (int i=0; i<m_Data.Size; i++)
			{
				Lifetime& lifetime = m_Data.Lifetime[i];
				if (lifetime.Current <= 0)
				{
					// Destory Entity
					registry.Remove(m_Data.Entity[i]);
				}
				else
				{
					lifetime.Current -= dt;
				}
			}
		}
		
	protected:
		void Reset(int index) override
		{
			m_Data.Lifetime[index].Current = 10;
			m_Data.Lifetime[index].Max = 10;
		}
		
		void Compact(int index, int lastIndex) override
		{
			m_Data.Lifetime[index] = m_Data.Lifetime[lastIndex];
		}
	};
	
}


#pragma once

#include <array>
#include "../ecs2/Entity.h"
#include "../ecs2/ComponentStorage.h"

namespace ecs2
{
	struct Lifetime
	{
		float Current;
		float Max;
	};
	
	// コンポーネント
	struct LifetimeComponent
	{
		static const int MAX_COMPONENT = 128;
		
		// 必須
		int size = 0;
		std::array<Entity, MAX_COMPONENT> entity;
		
		// ユーザー定義
		std::array<Lifetime, MAX_COMPONENT> lifetime;
	};
	
	class LifetimeComponentStorage : public ComponentStorage<LifetimeComponent>
	{
	public:
		Lifetime& GetLifetime(ComponentHandle handle)
		{
			return m_Data.lifetime[handle.index];
		}
		
		void Update(EntityRegistry& registry, float dt) override
		{
			for (int i=0; i<m_Data.size; i++)
			{
				Lifetime& lifetime = m_Data.lifetime[i];
				if (lifetime.Current <= 0)
				{
					// Destory Entity
					registry.Destroy(m_Data.entity[i]);
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
			m_Data.lifetime[index].Current = 10;
			m_Data.lifetime[index].Max = 10;
		}
		
		void Compact(int index, int lastIndex) override
		{
			m_Data.lifetime[index] = m_Data.lifetime[lastIndex];
		}
	};
	
}


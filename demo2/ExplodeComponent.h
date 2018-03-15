#pragma once

#include <array>
#include "../ecs2/Entity.h"
#include "../ecs2/ComponentSystem.h"
#include <iostream>

namespace ecs2
{
	// コンポーネント
	struct ExplodeComponent
	{
		static const int MAX_COMPONENT = 128;
		
		// 必須
		int Size = 0;
		std::array<Entity, MAX_COMPONENT> Entity;
		
		// ユーザー定義
		std::array<int, MAX_COMPONENT> ExplodePerticileId;
	};
	
	
	class ExplodeComponentSystem : public ComponentSystem<ExplodeComponent>, public IEntityEventListener
	{
		class TransformComponentSystem* m_TransformComponentSystem = nullptr;

	public:

		int GetExplodePerticileId(ComponentHandle handle)
		{
			return m_Data.ExplodePerticileId[handle.index];
		}

		void OnCreateEntity(Entity entity) override;

		void OnRemoveEntity(Entity entity) override;
		
	protected:
		void Reset(int index) override
		{
			m_Data.ExplodePerticileId[index] = 0;
		}
		
		void Compact(int index, int lastIndex) override
		{
			m_Data.ExplodePerticileId[index] = m_Data.ExplodePerticileId[lastIndex];
		}
	};

}

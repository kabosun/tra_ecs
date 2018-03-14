#pragma once

#include <array>
#include "../ecs2/Entity.h"
#include "../ecs2/ComponentStorage.h"

namespace ecs2
{
	// コンポーネント
	struct TransformComponent
	{
		static const int MAX_COMPONENT = 128;
		
		// 必須
		int Size = 0;
		std::array<Entity, MAX_COMPONENT> Entity;
		
		// ユーザー定義
		std::array<Vector2f, MAX_COMPONENT> Position;
	};
	
	
	class TransformComponentStorage : public ComponentStorage<TransformComponent>
	{
	public:
		Vector2f& GetPosition(ComponentHandle handle)
		{
			return m_Data.Position[handle.index];
		}
		
	protected:
		void Reset(int index) override
		{
			m_Data.Position[index].X = 0;
			m_Data.Position[index].Y = 0;
		}
		
		void Compact(int index, int lastIndex) override
		{
			m_Data.Position[index] = m_Data.Position[lastIndex];
		}
	};

}

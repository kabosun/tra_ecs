#pragma once

#include <array>
#include "../ecs2/Entity.h"
#include "../ecs2/ComponentSystem.h"

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
		std::array<Vector3f, MAX_COMPONENT> Position;
		std::array<float, MAX_COMPONENT> Rotation;
		std::array<Vector3f, MAX_COMPONENT> Scale;
	};
	
	
	class TransformComponentSystem : public ComponentSystem<TransformComponent>
	{
	public:
		Vector3f& GetPosition(ComponentHandle handle)
		{
			return m_Data.Position[handle.index];
		}

		float& GetRotation(ComponentHandle handle)
		{
			return m_Data.Rotation[handle.index];
		}

		Vector3f& GetScale(ComponentHandle handle)
		{
			return m_Data.Scale[handle.index];
		}
		
	protected:
		void Reset(int index) override
		{
		}
		
		void Compact(int index, int lastIndex) override
		{
			m_Data.Position[index] = m_Data.Position[lastIndex];
			m_Data.Rotation[index] = m_Data.Rotation[lastIndex];
			m_Data.Scale[index] = m_Data.Scale[lastIndex];
		}
	};

}

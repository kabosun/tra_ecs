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
		int size = 0;
		std::array<Entity, MAX_COMPONENT> entity;
		
		// ユーザー定義
		std::array<Vector2f, MAX_COMPONENT> position;
		std::array<Vector2f, MAX_COMPONENT> velocity;
		std::array<Vector2f, MAX_COMPONENT> accelaration;
	};
	
	
	class TransformComponentStorage : public ComponentStorage<TransformComponent>
	{
	public:
		Vector2f& GetPosition(ComponentHandle handle)
		{
			return m_Data.position[handle.index];
		}
		
		Vector2f& GetVelocity(ComponentHandle handle)
		{
			return m_Data.velocity[handle.index];
		}
		
		Vector2f& GetAccelaration(ComponentHandle handle)
		{
			return m_Data.accelaration[handle.index];
		}
		
		void Update(EntityRegistry& registry, float dt) override
		{
			for (int i=0; i<m_Data.size; i++)
			{
				Vector2f& position = m_Data.position[i];
				Vector2f& velocity = m_Data.velocity[i];
				Vector2f& accelaration = m_Data.accelaration[i];
				
				velocity.X += accelaration.X * dt;
				velocity.Y += accelaration.Y * dt;
				
				position.X += velocity.X * dt;
				position.Y += velocity.Y * dt;
			}
		}
		
	protected:
		void Reset(int index) override
		{
			m_Data.position[index].X = 0;
			m_Data.position[index].Y = 0;
			m_Data.velocity[index].X = 0;
			m_Data.velocity[index].Y = 0;
			m_Data.accelaration[index].X = 0;
			m_Data.accelaration[index].Y = 0;
		}
		
		void Compact(int index, int lastIndex) override
		{
			m_Data.position[index] = m_Data.position[lastIndex];
			m_Data.velocity[index] = m_Data.velocity[lastIndex];
			m_Data.accelaration[index] = m_Data.accelaration[lastIndex];
		}
	};

}

#pragma once

#include <array>
#include "../ecs2/Entity.h"
#include "../ecs2/ComponentStorage.h"
#include <iostream>

namespace ecs2
{
	// コンポーネント
	struct PhysicsComponent
	{
		static const int MAX_COMPONENT = 128;
		
		// 必須
		int Size = 0;
		std::array<Entity, MAX_COMPONENT> Entity;
		
		// ユーザー定義
		std::array<Vector2f, MAX_COMPONENT> Velocity;
		std::array<Vector2f, MAX_COMPONENT> Accelaration;
	};
	
	
	class PhysicsComponentStorage : public ComponentStorage<PhysicsComponent>, public IUpdatable, public IEntityEventListener
	{
		class TransformComponentStorage* m_TransformComponentStorage = nullptr;

	public:

		void Depends(TransformComponentStorage* s)
		{
			m_TransformComponentStorage = s;
		}

		Vector2f& GetVelocity(ComponentHandle handle)
		{
			return m_Data.Velocity[handle.index];
		}

		Vector2f& GetAccelaration(ComponentHandle handle)
		{
			return m_Data.Accelaration[handle.index];
		}

		void Update(EntityRegistry& registry, float dt) override;

		void OnCreateEntity(Entity entity) override;

		void OnRemoveEntity(Entity entity) override;
		
	protected:
		void Reset(int index) override
		{
			m_Data.Velocity[index].X = 0;
			m_Data.Velocity[index].Y = 0;
			m_Data.Accelaration[index].X = 0;
			m_Data.Accelaration[index].Y = 0;
		}
		
		void Compact(int index, int lastIndex) override
		{
			m_Data.Velocity[index] = m_Data.Velocity[lastIndex];
			m_Data.Accelaration[index] = m_Data.Accelaration[lastIndex];
		}
	};

}

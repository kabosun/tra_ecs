#include "PhysicsComponent.h"
#include "TransformComponent.h"

namespace ecs2
{
	void PhysicsComponentStorage::Update(EntityRegistry& registry, float dt)
	{
		assert(m_TransformComponentStorage != nullptr);

		for (int i = 0; i<m_Data.Size; i++)
		{
			auto handle = m_TransformComponentStorage->GetHandle(m_Data.Entity[i]);
			Vector2f& position = m_TransformComponentStorage->GetPosition(handle);

			Vector2f& velocity = m_Data.Velocity[i];
			Vector2f& accelaration = m_Data.Accelaration[i];

			velocity.X += accelaration.X * dt;
			velocity.Y += accelaration.Y * dt;

			position.X += velocity.X * dt;
			position.Y += velocity.Y * dt;
		}
	}

	void PhysicsComponentStorage::OnCreateEntity(Entity entity)
	{}

	void PhysicsComponentStorage::OnRemoveEntity(Entity entity)
	{}
}

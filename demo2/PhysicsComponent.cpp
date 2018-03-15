#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "ComponentSystemRegistry.h"
#include <cassert>

namespace ecs2
{
	void PhysicsComponentSystem::Update(EntityRegistry* eRegistry, float dt)
	{
		auto m_TransformComponentSystem = this->m_CSRegistry->Get<TransformComponentSystem>();
		assert(m_TransformComponentSystem != nullptr);

		for (int i = 0; i<m_Data.Size; i++)
		{
			auto handle = m_TransformComponentSystem->GetHandle(m_Data.Entity[i]);
			Vector3f& position = m_TransformComponentSystem->GetPosition(handle);

			Vector3f& velocity = m_Data.Velocity[i];
			Vector3f& accelaration = m_Data.Acceleration[i];

			velocity += accelaration * dt;
			position += velocity * dt;
		}
	}

	void PhysicsComponentSystem::OnCreateEntity(Entity entity)
	{}

	void PhysicsComponentSystem::OnRemoveEntity(Entity entity)
	{}
}

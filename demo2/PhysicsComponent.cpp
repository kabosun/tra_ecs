#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "../ecs2/ComponentSystemRegistry.h"

namespace ecs2
{
	void PhysicsComponentSystem::Update(EntityRegistry* eRegistry, float dt)
	{
		auto transformComponentSystem = this->m_CSRegistry->Get<TransformComponentSystem>();

		for (int i = 0; i<m_Data.Size; i++)
		{
			auto handle = transformComponentSystem->GetHandle(m_Data.Entity[i]);
			Vector3f& position = transformComponentSystem->GetPosition(handle);

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

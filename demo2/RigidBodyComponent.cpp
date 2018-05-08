#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "../ecs2/ComponentRegistry.h"

void RigidBodyComponent::Update(EntityRegistry& registry, float dt)
{
	/*auto&& transformComponent = ComponentRegistry()->GetComponent<TransformComponent>();

	for (int i = 0; i<Size(); i++)
	{
		auto handle = transformComponent->GetHandle(GetEntity(i));
		Vector3f position = transformComponent->GetPosition(handle);

		Vector3f& velocity = m_Data.Velocity[i];
		Vector3f& accelaration = m_Data.Acceleration[i];
		m_Data.Velocity[i] *= m_Data.Friction[i];

		velocity += accelaration * dt;
		position += velocity * dt;

		transformComponent->SetPosition(handle, position);
	}*/
}

void RigidBodyComponent::OnCreateEntity(Entity entity)
{}

void RigidBodyComponent::OnRemoveEntity(Entity entity)
{}

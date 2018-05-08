
#include "LifetimeComponent.h"
#include "../ecs2/EntityRegistry.h"
#include "../ecs2/ComponentRegistry.h"

void LifetimeComponent::Update(EntityRegistry& registry, float dt)
{
	for (int i=0; i<Size(); i++)
	{
		Lifetime& lifetime = m_Data.Lifetime[i];
		if (lifetime.Current <= 0)
		{
			// Destory Entity
			registry.Remove(GetEntity(i));
		}
		else
		{
			lifetime.Current -= dt;
		}
	}
}

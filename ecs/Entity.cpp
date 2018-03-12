#include "Entity.h"
#include "World.h"

void Entity::AddComponent(ComponentTypeId type)
{
	World::GetInstance().AttachComponent(*this, type);
}

IComponent* Entity::GetComponent(ComponentTypeId type) const
{
	return World::GetInstance().GetRegistry(type)->GetComponent(*this);
}

void Entity::Kill()
{
	World::GetInstance().KillEntity(*this);
}

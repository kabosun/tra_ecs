#include "Entity.h"
#include "World.h"

void Entity::AddComponent(const Entity& entity, ComponentTypeId type)
{
	World::GetInstance().AttachComponent(entity, type);
}

IComponent* Entity::GetComponent(ComponentTypeId type) const
{
	return World::GetInstance().GetStorage(type)->GetComponent(*this);
}

void Entity::Kill()
{
	World::GetInstance().KillEntity(*this);
}

#include "Entity.h"
#include "World.h"

void Entity::AddComponent(Entity& entity, ComponentTypeId type)
{
	World::GetInstance().AttachComponent(entity, type);
}

void Entity::Kill()
{
	World::GetInstance().KillEntity(*this);
}
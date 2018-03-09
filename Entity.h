#pragma once

using EntityId = unsigned int;
using ComponentTypeId = unsigned int;

template<typename T>
class Component
{
public:
	static const ComponentTypeId COMPONENT_TYPE;

	EntityId EntityId;

	Component()
	{
	}
};
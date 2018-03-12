#pragma once

#include <vector>
#include <memory>
#include "Entity.h"

class IComponent
{
};

template<typename T>
class Component : public IComponent
{
public:
	static const ComponentTypeId TypeId;

	EntityId EntityId;
};

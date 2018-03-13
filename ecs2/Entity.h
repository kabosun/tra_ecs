#pragma once

namespace ecs2
{
	using EntityId = unsigned int;
	
	const unsigned ENTITY_INDEX_BITS = 22;
	const unsigned ENTITY_INDEX_MASK = (1<<ENTITY_INDEX_BITS)-1;

	const unsigned ENTITY_GENERATION_BITS = 8;
	const unsigned ENTITY_GENERATION_MASK = (1<<ENTITY_GENERATION_BITS)-1;

	struct Entity
	{
		EntityId Id;
		
		static Entity Make(unsigned int index, unsigned char generation)
		{
			Entity entity = {(generation << ENTITY_INDEX_BITS) | index};
			return entity;
		}
		
		unsigned int Index() const
		{
			return Id & ENTITY_INDEX_MASK;
		}
		
		unsigned int Generation() const
		{
			return (Id >> ENTITY_INDEX_BITS) & ENTITY_GENERATION_MASK;
		}
		
		bool operator==(const Entity& e) const
		{
			return Id == e.Id;
		}
		
		bool operator!=(const Entity& e) const
		{
			return Id != e.Id;
		}
	};

}

#pragma once

#include <vector>
#include <memory>
#include "Entity.h"

class EntityStorage
{
	EntityId m_EntityIdCoutner = 0;

	// エンティティのリスト。順番は要素削除のたびに入れ替わる。
	std::vector<Entity> m_Entities;

public:

	Entity& CreateEntity()
	{
		m_EntityIdCoutner++;

		m_Entities.emplace_back(m_EntityIdCoutner);

		return m_Entities.back();
	}

	Entity& Add(const Entity& entity)
	{
		m_Entities.push_back(entity);
		return m_Entities.back();
	}

	void Remove(const Entity& entity)
	{
		// entityはstorageとsystemで別々のリストが管理されていてアドレスが異なる場合があるので、この処理はうまくいかない
		size_t a = &entity;
		size_t b = &m_Entities[0];
		size_t index = a - b;
		m_Entities[index] = m_Entities.back();
		m_Entities.pop_back();
	}

	void Clear()
	{
		m_Entities.clear();
	}

	std::vector<Entity> GetEntities() const
	{
		return m_Entities;
	}


};

#include "ExplodeComponent.h"
#include "TransformComponent.h"
#include <iostream>
#include <cassert>

namespace ecs2
{
	void ExplodeComponentStorage::OnCreateEntity(Entity entity)
	{}

	void ExplodeComponentStorage::OnRemoveEntity(Entity entity)
	{
		assert(m_TransformComponentStorage != nullptr);

		auto handle = m_TransformComponentStorage->GetHandle(entity);
		auto position = m_TransformComponentStorage->GetPosition(handle);

		// entityがなくなったら爆発エフェクトを発生させる
		std::cout << "Emit Explode Perticle. ID:" << entity.Index() << "(" << entity.Generation() << ") X:" << position.X << " Y:" << position.Y << std::endl;
	}

}

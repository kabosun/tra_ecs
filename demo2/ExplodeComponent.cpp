#include "ExplodeComponent.h"
#include "TransformComponent.h"
#include "ComponentSystemRegistry.h"
#include <iostream>

namespace ecs2
{
	void ExplodeComponentSystem::OnCreateEntity(Entity entity)
	{}

	void ExplodeComponentSystem::OnRemoveEntity(Entity entity)
	{
		auto m_TransformComponentSystem = m_CSRegistry->Get<TransformComponentSystem>();

		auto handle = m_TransformComponentSystem->GetHandle(entity);
		auto& position = m_TransformComponentSystem->GetPosition(handle);

		// entityがなくなったら爆発エフェクトを発生させる
		std::cout << "Emit Explode Perticle. ID:" << entity.Index() << "(" << entity.Generation() << ") X:" << position.X << " Y:" << position.Y << std::endl;
	}
}

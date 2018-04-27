#pragma once

#include <array>
#include "../ecs2/Entity.h"
#include "../ecs2/ComponentSystem.h"

namespace ecs2
{
	// コンポーネント
	struct TransformComponent
	{
		static const int MAX_COMPONENT = 128;
		
		// 必須
		int Size = 0;
		std::array<Entity, MAX_COMPONENT> Entity;
		
		// ユーザー定義
		std::array<Vector3f, MAX_COMPONENT> Position;
		std::array<float, MAX_COMPONENT> Rotation;
		std::array<Vector3f, MAX_COMPONENT> Scale;
	};
	
	
	class TransformComponentSystem : public ComponentSystem<TransformComponent>, public IEntityEventListener
	{
	public:
		Vector3f GetPosition(ComponentHandle handle) const
		{
			return m_Data.Position[handle.index];
		}
		
		void SetPosition(ComponentHandle handle, Vector3f& position)
		{
			m_Data.Position[handle.index] = position;
		}

		float GetRotation(ComponentHandle handle) const
		{
			return m_Data.Rotation[handle.index];
		}
		
		void SetRotation(ComponentHandle handle, float rotation)
		{
			m_Data.Rotation[handle.index] = rotation;
		}

		Vector3f GetScale(ComponentHandle handle) const
		{
			return m_Data.Scale[handle.index];
		}
		
		void SetScale(ComponentHandle handle, Vector3f& scale)
		{
			m_Data.Scale[handle.index] = scale;
		}
		
		void OnCreateEntity(Entity entity) override
		{}
		
		void OnRemoveEntity(Entity entity) override
		{}
		
	protected:
		void Reset(int index) override
		{
		}
		
		void Compact(int index, int lastIndex) override
		{
			m_Data.Position[index] = m_Data.Position[lastIndex];
			m_Data.Rotation[index] = m_Data.Rotation[lastIndex];
			m_Data.Scale[index] = m_Data.Scale[lastIndex];
		}
	};

	class TransformFacade
	{
		TransformComponentSystem* component;
		Entity entity;
		ComponentHandle handle;
	public:
		static TransformFacade Create(Entity entity, TransformComponentSystem* component)
		{
			TransformFacade facade;
			facade.entity = entity;
			facade.component = component;
			facade.handle = component->GetHandle(entity);
			
			return facade;
		}
		
		Vector3f GetPosition() const
		{
			return component->GetPosition(handle);
		}
		
		void SetPosition(Vector3f& position)
		{
			return component->SetPosition(handle, position);
		}
	};
}

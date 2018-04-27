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
		
		void SetPosition(ComponentHandle handle, const Vector3f& position)
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
		
		void SetScale(ComponentHandle handle, const Vector3f& scale)
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
		
		void SetPosition(const Vector3f& position)
		{
			component->SetPosition(handle, position);
		}

		float GetRotation() const
		{
			return component->GetRotation(handle);
		}

		void SetRotation(float rotation)
		{
			component->SetRotation(handle, rotation);
		}

		Vector3f GetScale() const
		{
			return component->GetScale(handle);
		}

		void SetScale(const Vector3f& scale)
		{
			component->SetScale(handle, scale);
		}
	};
}

#pragma once

#include <array>
#include "../ecs2/Entity.h"
#include "../ecs2/ComponentSystem.h"
#include <iostream>

namespace ecs2
{
	// コンポーネント
	struct PhysicsComponent
	{
		static const int MAX_COMPONENT = 128;
		
		// 必須
		int Size = 0;
		std::array<Entity, MAX_COMPONENT> Entity;
		
		// ユーザー定義
		std::array<Vector3f, MAX_COMPONENT> Velocity;
		std::array<Vector3f, MAX_COMPONENT> Acceleration;
	};
	
	
	class PhysicsComponentSystem : public ComponentSystem<PhysicsComponent>, public IUpdatable, public IEntityEventListener
	{
	public:

		Vector3f& GetVelocity(ComponentHandle handle)
		{
			return m_Data.Velocity[handle.index];
		}

		Vector3f& GetAccelaration(ComponentHandle handle)
		{
			return m_Data.Acceleration[handle.index];
		}

		void Update(EntityRegistry* eRgistry, float dt) override;

		void OnCreateEntity(Entity entity) override;

		void OnRemoveEntity(Entity entity) override;
		
	protected:
		void Reset(int index) override
		{
		}
		
		void Compact(int index, int lastIndex) override
		{
			m_Data.Velocity[index] = m_Data.Velocity[lastIndex];
			m_Data.Acceleration[index] = m_Data.Acceleration[lastIndex];
		}
	};

	class PhysicsFacade
	{
		PhysicsComponentSystem* component;
		Entity entity;
	public:
		static PhysicsFacade Create(Entity entity, PhysicsComponentSystem* component)
		{
			PhysicsFacade facade;
			facade.entity = entity;
			facade.component = component;
			
			return facade;
		}
		
		Vector3f GetVelocity() const
		{
			ComponentHandle handle = component->GetHandle(entity);
			return component->GetVelocity(handle);
		}
		
		void SetVelocity(Vector3f& velocity)
		{
			ComponentHandle handle = component->GetHandle(entity);
			auto&& value = component->GetVelocity(handle);
			value = velocity;
		}
		
		Vector3f GetAccelaration() const
		{
			ComponentHandle handle = component->GetHandle(entity);
			return component->GetAccelaration(handle);
		}
		
		void SetAccelaration(Vector3f& accelaration)
		{
			ComponentHandle handle = component->GetHandle(entity);
			auto&& value = component->GetAccelaration(handle);
			value = accelaration;
		}
	};
}

#pragma once

#include <vector>
#include <map>
#include <memory>
#include "ECS.h"
#include "Event.h"

class WorldSystem
{
	EventHandler* EventHandler;
	EntityRegistry EntityRegistry;
	std::map<ComponentTypeId, std::shared_ptr<IComponentRegistry>> ComponentRegistryMap;

public:

	WorldSystem()
	{
	}

	virtual ~WorldSystem() {}

	std::vector<std::shared_ptr<ISystem>> Systems;

	template<typename T>
	ComponentRegistry<T>& GetRegistry()
	{
		auto a = ComponentRegistry<T>();
		return a;
	}

	void KillEntity(const EntityId id)
	{
		EntityDeadEvent e = { id };
		EventHandler->SendEvent<EntityDeadEvent>(e);
	}

	template<typename T>
	void AddComponentRegistry()
	{
		IComponentRegistry* registry = new ComponentRegistry<T>();

		ComponentRegistryMap.insert(std::make_pair(T::COMPONENT_TYPE, std::shared_ptr<IComponentRegistry>(registry)));
	}

	template<typename T>
	void AddSystem()
	{
		ISystem* system = new T();
		Systems.push_back(std::shared_ptr<ISystem>(system));
	}

	EntityId CreateEntity()
	{
		return EntityRegistry.CreateEntity();
	}

	template<typename T>
	void AttachComponent(EntityId EntityId)
	{
		std::shared_ptr<IComponentRegistry> registry = ComponentRegistryMap.at(T::COMPONENT_TYPE);

		registry->CreateComponent(EntityId);
		
	}
};

// ����
class PhysicsSystem : public System<PhysicsSystem>
{

};

// ��ѓ���̐������ԂƂ����Ǘ�����
class LifetimeSystem : public System<LifetimeSystem>
{
	WorldSystem* WorldSystem;

public:

	void Update(DeltaFrame dt) override
	{
		for (LifetimeComponent& c : WorldSystem->GetRegistry<LifetimeComponent>().Components)
		{
			if (c.current_lifetime >= 0)
			{
				// ���S�ʒm
				WorldSystem->KillEntity(c.EntityId);
			}
			else
			{
				c.current_lifetime--;
			}
		}
	}
};

// ��ѓ���
class ProjectileSystem : public System<ProjectileSystem>
{
	WorldSystem* WorldSystem;

public:

	ProjectileSystem()
	{
		// Add collision Callback Fuction.
	}

	void Update(DeltaFrame dt) override
	{
	}

	void OnCollisionBegin(CollisionBeginEvent& e)
	{

	}

	void OnCollisionEnd(CollisionBeginEvent& e)
	{
		// �Ԃ���������ł�����
		WorldSystem->KillEntity(e.a.EntityId);

		// TODO ���ŃG�t�F�N�g�𔭐�������
	}
};

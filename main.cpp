#include <iostream>
#include <memory>
#include "demo2/ECS2.h"

using namespace ecs2;

enum ComponentType
{
	TRANSFORM = 1,
	PHYSICS = 2,
	LIFETIME = 4,
	HEALTH = 8,
	EXPLODE = 16,
	ALL = 31,
};


int main(int argc, const char * argv[]) {

	ecs2::mt.seed(ecs2::rand());

	// サンプル
	auto registry = std::make_shared<EntityRegistry>();

	ComponentSystemRegistry componentSystemRegistry(registry);
	componentSystemRegistry.Add<TransformComponentSystem>();
	componentSystemRegistry.AddUpdatable<PhysicsComponentSystem>();
	componentSystemRegistry.AddUpdatable<LifetimeComponentSystem>();
	componentSystemRegistry.AddUpdatable<HealthComponentSystem>();
	componentSystemRegistry.Add<ExplodeComponentSystem>();

	auto transformComponent = componentSystemRegistry.Get<TransformComponentSystem>();
	auto physicsComponent = componentSystemRegistry.Get<PhysicsComponentSystem>();
	auto lifetimeComponent = componentSystemRegistry.Get<LifetimeComponentSystem>();
	auto healthComponent = componentSystemRegistry.Get<HealthComponentSystem>();
	auto explodeComponent = componentSystemRegistry.Get<ExplodeComponentSystem>();

	// event
	registry->AddEventListener(explodeComponent.get());


	float dt = 1.0f;
	for (int i=0; i<128; i++)
	{
		std::cout << "Frame:" << i << std::endl;

		{
			Entity e = registry->Create();
			EntityFacade entity = EntityFacade(&componentSystemRegistry, e);

			entity.CreateComponent(ComponentType::ALL);

			Vector3f position(10, 20, 0);
			entity.Transform().SetPosition(position);

			Vector3f velocity(5, 3.5, 0);
			entity.Physics().SetVelocity(velocity);

			Health health(100, 100);
			entity.Health().SetHealth(health);

			std::cout << "Create ID:" << e.Index() << " (" << e.Generation() << ") X:" << position.X << " Y:" << position.Y << std::endl;
		}

		componentSystemRegistry.Update(dt);

		componentSystemRegistry.GC();


		std::cout << "StorageSize:" << transformComponent->Size() << std::endl;
	}
#ifdef _MSC_VER
	std::getchar();
#endif
	return 0;
}

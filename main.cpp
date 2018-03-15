#include <iostream>
#include <memory>
#include "demo2/ECS2.h"

using namespace ecs2;

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
	registry->AddListener(explodeComponent.get());

	
	float dt = 1.0f;
	for (int i=0; i<128; i++)
	{
		std::cout << "Frame:" << i << std::endl;

		Entity e = registry->Create();
		transformComponent->Create(e);
		physicsComponent->Create(e);
		lifetimeComponent->Create(e);
		healthComponent->Create(e);
		explodeComponent->Create(e);
		
		// transform
		auto transformHandle = transformComponent->GetHandle(e);
		
		auto&& position = transformComponent->GetPosition(transformHandle);
		position.X = 10;
		position.Y = 20;
		position.Z = 0;
		
		auto&& velocity = physicsComponent->GetVelocity(transformHandle);
		velocity.X = 5.0;
		velocity.Y = 3.5;
		velocity.Z = 0.0;

		// health
		auto healthHandle = healthComponent->GetHandle(e);
		auto&& health = healthComponent->GetHealth(healthHandle);
		health.Max = 100;
		health.Current = 100;

		std::cout << "Create ID:" << e.Index() << " (" << e.Generation() << ") X:" << position.X << " Y:" << position.Y << std::endl;
		
		
		componentSystemRegistry.Update(dt);
		
		componentSystemRegistry.GC();
		
		
		std::cout << "StorageSize:" << transformComponent->Size() << std::endl;
	}
#ifdef _MSC_VER
	std::getchar();
#endif
	return 0;
}

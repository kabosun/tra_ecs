#include <iostream>
#include <memory>
#include "demo2/ECS2.h"
#include "demo2/Facade.h"
#include "demo2/Physics.h"

using namespace ecs2;

int main(int argc, const char * argv[]) {

	ecs2::mt.seed(ecs2::rand());
	
	const int MAX_COMPONENT = 128;

	Physics physics;
	EntityRegistry entityRegistry;
	ComponentRegistry registry(&entityRegistry);
	auto transformComponent = registry.AddComponent<TransformComponent>();
	auto rigidbodyComponent = registry.AddUpdatableComponent<RigidBodyComponent>();
	auto lifetimeComponent = registry.AddUpdatableComponent<LifetimeComponent>();
	auto healthComponent = registry.AddUpdatableComponent<HealthComponent>();
	auto explodeComponent = registry.AddComponent<ExplodeComponent>();
	auto ballbehaviorComponent = registry.AddUpdatableComponent<BallBehaviorComponent>();

	transformComponent->Initialize(entityRegistry, MAX_COMPONENT);
	rigidbodyComponent->Initialize(entityRegistry, MAX_COMPONENT);
	lifetimeComponent->Initialize(entityRegistry, MAX_COMPONENT);
	healthComponent->Initialize(entityRegistry, MAX_COMPONENT);
	explodeComponent->Initialize(entityRegistry, MAX_COMPONENT);
	ballbehaviorComponent->Initialize(entityRegistry, MAX_COMPONENT);
	
	float dt = 1.0f;
	
	// init
	int width = 200;
	int height = 200;
	int block_left = (width - 50) / 2;
	int block_top = 30;
	
	// block
	for (int i=0; i<10; i++)
	{
		Entity e = registry.CreateEntity();
		transformComponent->Attach(e);
		rigidbodyComponent->Attach(e);
		lifetimeComponent->Attach(e);
		
		EntityFacade entity = EntityFacade(&registry, e);
		entity.Transform().SetPosition(Vector3f(block_left + i%5*20, block_top + i/5*10, 0));
		entity.Lifetime().SetLifetime(Health(10, 10));
	}
	
	// ball
	for (int i=0; i<2; i++)
	{
		Entity e = registry.CreateEntity();
		transformComponent->Attach(e);
		rigidbodyComponent->Attach(e);
		healthComponent->Attach(e);
		
		EntityFacade entity = EntityFacade(&registry, e);
		entity.Transform().SetPosition(Vector3f(width/2, height/2+50, 0));
		entity.Physics().SetVelocity(Vector3f(0, 1, 0));
		entity.Health().SetHealth(Health(1, 1));
		
	}
	
	for (int i=0; i<128; i++)
	{
		std::cout << "Frame:" << i << std::endl;

		registry.Update(dt);
		
		physics.Update(dt);

		registry.GC();

		std::cout << "StorageSize:" << transformComponent->Size() << std::endl;
	}
#ifdef _MSC_VER
	std::getchar();
#endif
	return 0;
}

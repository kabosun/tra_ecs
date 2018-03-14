#include <iostream>
#include "demo2/TransformComponent.h"
#include "demo2/PhysicsComponent.h"
#include "demo2/LifetimeComponent.h"
#include "demo2/HealthComponent.h"
#include "demo2/ExplodeComponent.h"

using namespace ecs2;

int main(int argc, const char * argv[]) {
	
	Initialize();
	
	// サンプル
	EntityRegistry registry;
	TransformComponentStorage transformComponent;
	PhysicsComponentStorage physicsComponent;
	LifetimeComponentStorage lifetimeComponent;
	HealthComponentStorage healthComponent;
	ExplodeComponentStorage explodeComponent;

	// depends
	physicsComponent.Depends(&transformComponent);
	explodeComponent.Depends(&transformComponent);

	// event
	registry.AddListener(&explodeComponent);



	std::vector<IUpdatable*> updatableComponents = {
		&physicsComponent,
		&lifetimeComponent,
		&healthComponent,
	};

	std::vector<IGarbageCollectable*> gcComponents = {
		&transformComponent,
		&physicsComponent,
		&lifetimeComponent,
		&healthComponent,
		&explodeComponent,
	};
	
	for (int i=0; i<128; i++)
	{
		std::cout << "Frame:" << i << std::endl;

		Entity e = registry.Create();
		transformComponent.Create(e);
		physicsComponent.Create(e);
		lifetimeComponent.Create(e);
		healthComponent.Create(e);
		explodeComponent.Create(e);
		
		// transform
		auto transformHandle = transformComponent.GetHandle(e);
		
		auto&& position = transformComponent.GetPosition(transformHandle);
		position.X = 10;
		position.Y = 20;
		
		auto&& velocity = physicsComponent.GetVelocity(transformHandle);
		velocity.X = 5.0;
		velocity.Y = 3.5;

		// health
		auto healthHandle = healthComponent.GetHandle(e);
		auto&& health = healthComponent.GetHealth(healthHandle);
		health.Max = 100;
		health.Current = 100;

		std::cout << "Create ID:" << e.Index() << " (" << e.Generation() << ") X:" << position.X << " Y:" << position.Y << std::endl;
		
		// Update
		float dt = 1.0f;
		for (auto&& component : updatableComponents)
		{
			component->Update(registry, dt);
		}
		
		// GC
		for (auto&& component : gcComponents)
		{
			component->GC(registry);
		}
		
		
		std::cout << "StorageSize:" << transformComponent.Size() << std::endl;
	}
#ifdef _MSC_VER
	std::getchar();
#endif
	return 0;
}

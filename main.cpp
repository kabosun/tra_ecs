//
//  main.cpp
//  ECS
//
//  Created by gladius on 2018/03/09.
//  Copyright © 2018年 gladius. All rights reserved.
//

#include <iostream>
#include "demo2/TransformComponent.h"
#include "demo2/LifetimeComponent.h"

using namespace ecs2;

int main(int argc, const char * argv[]) {
	// insert code here...
	std::cout << "Hello, World!\n";
	
	Initialize();
	
	EntityRegistry registry;
	TransformComponentStorage transform;
	LifetimeComponentStorage lifetime;
	
	for (int i=0; i<128; i++)
	{
		Entity e = registry.Create();
		transform.Create(e);
		lifetime.Create(e);
		
		auto handle = transform.Lookup(e);
		
		auto&& position = transform.GetPosition(handle);
		position.X = 10;
		position.Y = 20;
		
		auto&& velocity = transform.GetVelocity(handle);
		velocity.X = 5.0;
		velocity.Y = 3.5;
		
		float dt = 1.0f;
		transform.Update(registry, dt);
		lifetime.Update(registry, dt);
		
		std::cout << "ID:" << e.Index() << " g(" << e.Generation() << ") x:" << position.X << " y:" << position.Y << std::endl;
		
		// GC
		transform.GC(registry);
		
		
		std::cout << "Size:" << transform.Size() << std::endl;
		
	}
	
	return 0;
}

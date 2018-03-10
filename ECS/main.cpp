//
//  main.cpp
//  ECS
//
//  Created by gladius on 2018/03/09.
//  Copyright © 2018年 gladius. All rights reserved.
//

#include <iostream>
#include "ECS.h"

int main(int argc, const char * argv[]) {
	// insert code here...
	std::cout << "Hello, World!\n";
	
	std::cout << TransformComponent::COMPONENT_TYPE << std::endl;
	std::cout << PhysicsComponent::COMPONENT_TYPE << std::endl;
	std::cout << LifetimeComponent::COMPONENT_TYPE << std::endl;
	
	ECS();
	
	return 0;
}

#include "Core/SandBehaviour.h"
#include "Gamejam/Demo/Components/DemoCollisionComponent.h"
#include "Core/SandRemoverComponent.h"
#include <iostream>

jam::SandBehaviour::SandBehaviour(jecs::SystemManager& manager) :
	ISystemBehaviour<SandBrain>(manager)
{

}

void jam::SandBehaviour::Update()
{
	auto& brains = GetSet<SandBrain>();
	auto& colliders = GetSet<demo::DemoCollisionComponent>();
	auto& sandRemovers = GetSet<SandRemoverComponent>();

	const int32_t count = brains.GetCount();
	for (int32_t i = count - 1; i >= 0; --i)
	{
		const int32_t index = brains.dense[i];
		auto& collider = colliders.instances[index];

		bool remove = false;
		for (auto otherIndex : collider.collisions)
			if (sandRemovers.Contains(otherIndex))
			{
				remove = true;
				break;
			}

		if (remove)
			RemoveEntity(index);
	}
}

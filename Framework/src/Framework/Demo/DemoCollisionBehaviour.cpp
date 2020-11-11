#include "Gamejam/Demo/Behaviours/DemoCollisionBehaviour.h"
#include "Gamejam/Demo/Components/DemoTransformComponent.h"
#include "Gamejam/Demo/Components/DemoCollisionComponent.h"

jam::demo::DemoCollisionBehaviour::DemoCollisionBehaviour(jecs::SystemManager& manager) :
	ISystemBehaviour<DemoCollisionBehaviour>(manager)
{
}

void jam::demo::DemoCollisionBehaviour::Update()
{
	// Get all controller and transform entities. Make sure it's a reference.
	auto& colliders = GetSet<DemoCollisionComponent>();
	auto& transforms = GetSet<DemoTransformComponent>();

	// Iterate over colliders and update the transforms accordingly.
	const int32_t count = colliders.GetCount();
	for (int32_t i = 0; i < count; ++i)
	{
		const int32_t index = colliders.dense[i];
		const DemoCollisionComponent collider = *colliders[i];
		const DemoTransformComponent transform = transforms.instances[index];

		float xSize = transform.xScale * collider.xScale;

		for (int j = i + 1; j < count; ++j)
		{
			const int32_t otherIndex = colliders.dense[j];
			const DemoCollisionComponent otherCollider = *colliders[j];
			const DemoTransformComponent otherTransform = transforms.instances[otherIndex];

			//if(transform.x - transform.y)
		}
	}
}

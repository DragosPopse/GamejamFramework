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

	// Clear collisions from previous frame.
	for (int32_t i = 0; i < count; ++i)
		colliders[i]->collisions.clear();

	for (int32_t i = 0; i < count; ++i)
	{
		const int32_t index = colliders.dense[i];
		const DemoCollisionComponent collider = *colliders[i];
		const DemoTransformComponent transform = transforms.instances[index];

		const float xSize = transform.xScale * collider.xScale;
		const float ySize = transform.xScale * collider.yScale;

		for (int32_t j = i + 1; j < count; ++j)
		{
			const int32_t otherIndex = colliders.dense[j];
			const DemoCollisionComponent otherCollider = *colliders[j];
			const DemoTransformComponent otherTransform = transforms.instances[otherIndex];

			const float xOtherSize = otherTransform.xScale * otherCollider.xScale;
			const float yOtherSize = otherTransform.xScale * otherCollider.yScale;

			const float xDistance = abs(transform.x - otherTransform.x);
			const float yDistance = abs(transform.y - otherTransform.y);

			// Get intersect, and get the direction.
			float xIntersect = xSize + xOtherSize - xDistance;
			float yIntersect = ySize + yOtherSize - yDistance;

			// If distance is more than sizes combined it doesn't collide.
			if (xIntersect < 0 || yIntersect < 0)
				continue;

			const int horizontalPriority = xIntersect < yIntersect;

			if (transform.x > otherTransform.x)
				xIntersect *= -1;
			if (transform.y > otherTransform.y)
				yIntersect *= -1;

			// Check if triggers.
			if(!collider.isTrigger || !otherCollider.isTrigger)
			{
				DemoTransformComponent& a = transforms.instances[index];
				DemoTransformComponent& b = transforms.instances[otherIndex];

				// adjust position entities based on type.
				if(!collider.isStatic)
				{
					const float mul = otherCollider.isStatic ? 1 : .5;
					a.x -= xIntersect * mul * horizontalPriority;
					a.y -= yIntersect * mul * (1 - horizontalPriority);
				}

				if (!otherCollider.isStatic)
				{
					const float mul = collider.isStatic ? 1 : .5;
					b.x += xIntersect * mul * horizontalPriority;
					b.y += yIntersect * mul * (1 - horizontalPriority);
				}
			}

			DemoCollisionComponent& aCol = *colliders[i];
			DemoCollisionComponent& bCol = *colliders[j];

			aCol.collisions.push_back(j);
			bCol.collisions.push_back(i);
		}
	}
}

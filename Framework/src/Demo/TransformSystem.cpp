#include "Demo/ComponentSystems/TransformSystem.h"
#include "cECSar/ECSystemManager.h"
#include "Demo/Components/TransformComponent.h"

void jam::demo::TransformSystem::Update(cecsar::ECSystemManager& systemManager)
{
	auto& transforms = systemManager.GetSet<TransformComponent>();

	const int32_t count = transforms.GetCount();
	for (int32_t i = 0; i < count; ++i)
	{
		const int32_t index = transforms.m_dense[i];
		auto& transform = transforms.m_instances[index];

		// Set delta.
		transform.m_xDelta = transform.m_x - transform.m_xPrevious;
		transform.m_yDelta = transform.m_y - transform.m_yPrevious;

		transform.m_xPrevious = transform.m_x;
		transform.m_yPrevious = transform.m_y;
	}

	// Update positions.
	for (int32_t i = 0; i < count; ++i)
	{
		const int32_t index = transforms.m_dense[i];	
		auto& transform = transforms.m_instances[index];

		float xDelta = 0;
		float yDelta = 0;

		int32_t parentIndex = transform.m_parent;
		while(parentIndex != -1)
		{
			auto& parent = transforms.m_instances[parentIndex];
			xDelta += parent.m_xDelta;
			yDelta += parent.m_yDelta;
			parentIndex = parent.m_parent;
		}

		// move transform based on delta.
		transform.m_x += xDelta;
		transform.m_y += yDelta;
	}
}

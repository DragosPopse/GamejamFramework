#include "Demo/ComponentSystems/TransformSystem.h"
#include "cECSar/ECSystemManager.h"
#include "Demo/Components/TransformComponent.h"

void jam::demo::TransformSystem::Update(cecsar::ECSystemManager& systemManager)
{
	auto& transforms = systemManager.GetSet<TransformComponent>();

	const int32_t count = transforms.GetCount();
	for (int32_t i = 0; i < count; ++i)
	{
		const int32_t index = transforms.dense[i];
		auto& transform = transforms.instances[index];

		// Set delta.
		transform.m_xDelta = transform.x - transform.m_xPrevious;
		transform.m_yDelta = transform.y - transform.m_yPrevious;

		transform.m_xPrevious = transform.x;
		transform.m_yPrevious = transform.y;

		transform.m_degreesDelta = transform.degrees - transform.m_degreesPrevious;
		transform.m_degreesPrevious = transform.degrees;

		transform.m_xScaleDelta = transform.xScale - transform.m_xScalePrevious;
		transform.m_yScaleDelta = transform.yScale - transform.m_yScalePrevious;

		transform.m_xScalePrevious = transform.xScale;
		transform.m_yScalePrevious = transform.yScale;
	}

	// Update positions.
	for (int32_t i = 0; i < count; ++i)
	{
		const int32_t index = transforms.dense[i];	
		auto& transform = transforms.instances[index];

		float xDelta = 0;
		float yDelta = 0;

		float degreesDelta = 0;

		float xScaleDelta = 0;
		float yScaleDelta = 0;

		int32_t parentIndex = transform.parent;
		while(parentIndex != -1)
		{
			auto& parent = transforms.instances[parentIndex];
			xDelta += parent.m_xDelta;
			yDelta += parent.m_yDelta;

			degreesDelta += parent.m_degreesDelta;

			xScaleDelta += parent.m_xScaleDelta;
			yScaleDelta += parent.m_yScaleDelta;

			parentIndex = parent.parent;
		}

		// move transform based on delta.
		transform.x += xDelta;
		transform.y += yDelta;

		transform.degrees += degreesDelta;
		transform.xScale += xScaleDelta;
		transform.yScale += yScaleDelta;
	}
}

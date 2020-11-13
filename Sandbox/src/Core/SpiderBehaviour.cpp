#include "Core/SpiderBehaviour.h"
#include "Core/SmoothMovement.h"
#include "Core/AntBrain.h"
#include "Gamejam/Demo/Components/DemoTransformComponent.h"
#include "Core/AnimatorComponent.h"

jam::SpiderBehaviour::SpiderBehaviour(jecs::SystemManager& manager) :
	ISystemBehaviour<SpiderBrain>(manager)
{
}

void jam::SpiderBehaviour::Update()
{
	auto& spiders = GetSet<SpiderBrain>();
	auto& ants = GetSet<AntBrain>();

	auto& transforms = GetSet<demo::DemoTransformComponent>();
	auto& animators = GetSet<AnimatorComponent>();
	auto& smoothers = GetSet<SmoothMovement>();

	const int32_t count = spiders.GetCount();
	const int32_t antCount = ants.GetCount();

	for (int32_t i = 0; i < count; ++i)
	{
		const int32_t index = spiders.dense[i];
		const auto transform = transforms.instances[index];

		int32_t closest = -1;
		float closestDistance = 1e6;

		for (int32_t j = 0; j < antCount; ++j)
		{
			const int32_t antIndex = ants.dense[j];
			const auto antTransform = transforms.instances[antIndex];

			const float xDis = abs(transform.x - antTransform.x);
			const float yDis = abs(transform.y - antTransform.y);
			const float distance = sqrtf(pow(xDis, 2) + pow(yDis, 2));

			if (distance > closestDistance)
				continue;

			closestDistance = distance;
			closest = antIndex;
		}

		const bool found = closest != -1;
		auto& animator = animators.instances[index];
		auto& smoother = smoothers.instances[index];

		animator.paused = !found;

		if (!found)
			continue;

		const auto targetTransform = transforms.instances[closest];

		float xDir = transform.x - targetTransform.x;
		float yDir = transform.y - targetTransform.y;

		xDir /= closestDistance;
		yDir /= closestDistance;

		smoother.xDir = -xDir;
		smoother.yDir = -yDir;
	}
}

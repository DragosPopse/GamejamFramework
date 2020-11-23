#include "Demo/ComponentSystems/BatSystem.h"
#include "cECSar/ECSystemManager.h"
#include "Demo/Components/BatComponent.h"
#include "Gamejam/Core/App.hpp"
#include "Demo/Components/TransformComponent.h"
#include "Demo/Components/CameraTargetComponent.h"
#include "Demo/Components/ControllerComponent.h"

void jam::demo::BatSystem::Update(cecsar::ECSystemManager& systemManager)
{
	auto& bats = systemManager.GetSparseSet<BatComponent>();
	auto& transforms = systemManager.GetSparseSet<TransformComponent>();
	auto& targets = systemManager.GetMapSet<CameraTargetComponent>();
	auto& controllers = systemManager.GetSparseSet<ControllerComponent>();

	float xPosTarget = 0;
	float yPosTarget = 0;

	for (auto& keyPair : targets)
	{
		const int32_t index = keyPair.first;
		auto& transform = transforms.instances[index];

		xPosTarget += transform.xPosGlobal;
		yPosTarget += transform.yPosGlobal;
	}

	const int32_t targetSize = targets.size();
	xPosTarget /= targetSize;
	yPosTarget /= targetSize;

	const int32_t count = bats.GetCount();
	for (int32_t i = 0; i < count; ++i)
	{
		const int32_t index = bats.dense[i];
		auto& controller = controllers.instances[index];
		auto& transform = transforms.instances[index];

		const float xOffset = transform.xPosGlobal - xPosTarget;
		const float yOffset = transform.yPosGlobal - yPosTarget;

		const float magnitude = sqrtf(pow(xOffset, 2) + pow(yOffset, 2));

		if (magnitude == 0)
			continue;

		controller.xDir = -xOffset / magnitude;
		controller.yDir = -yOffset / magnitude;
	}
}

#include "Demo/ComponentSystems/MovementSystem.h"
#include "Demo/Components/MovementComponent.h"
#include "Demo/Components/TransformComponent.h"
#include <cstdint>
#include "cECSar/ECSystemManager.h"
#include "SDL_stdinc.h"
#include "Demo/Components/ControllerComponent.h"
#include "Demo/Modules/TimeModule.h"

void jam::demo::MovementSystem::Update(cecsar::ECSystemManager& systemManager)
{
	auto& movementComponents = systemManager.GetSparseSet<MovementComponent>();
	auto& controllerComponents = systemManager.GetSparseSet<ControllerComponent>();
	auto& transformComponents = systemManager.GetSparseSet<TransformComponent>();

	auto& timeModule = systemManager.GetModule<TimeModule>();
	const float deltaTime = timeModule.deltaTime;

	const int32_t count = movementComponents.GetCount();
	for (int32_t i = 0; i < count; ++i)
	{
		const int32_t index = movementComponents.dense[i];

		auto& movement = movementComponents.instances[index];
		auto& controller = controllerComponents.instances[index];
		auto& transform = transformComponents.instances[index];

		const float xDelta = controller.xDir * movement.movementSpeed * deltaTime;
		const float yDelta = controller.yDir * movement.movementSpeed * deltaTime;

		transform.xPos += xDelta;
		transform.yPos += yDelta;

		const bool rotate = abs(xDelta) > 0 || abs(yDelta) > 0;
		if (!rotate)
			continue;

		float targetDegrees = atan2f(controller.xDir, -controller.yDir) * 180 / M_PI;
		if (targetDegrees < 0)
			targetDegrees += 360;

		const float currentDegrees = transform.degrees - floor(transform.degrees / 360) * 360;

		bool dir = currentDegrees > targetDegrees;
		const bool reverse = std::abs(currentDegrees - targetDegrees) < 180;
		if (reverse)
			dir = !dir;

		const float delta = movement.rotationSpeed * (dir * 2 - 1) * deltaTime;
		transform.degrees = currentDegrees + delta;
	}
}

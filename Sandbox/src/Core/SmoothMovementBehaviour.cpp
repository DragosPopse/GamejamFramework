#include "Core/SmoothMovementBehaviour.h"
#include "Gamejam/Demo/Components/DemoTransformComponent.h"
#include "SDL_stdinc.h"

jam::SmoothMovementBehaviour::SmoothMovementBehaviour(jecs::SystemManager& manager) :
	ISystemBehaviour<jam::SmoothMovement>(manager)
{
}

void jam::SmoothMovementBehaviour::Update(const float deltaTime)
{
	auto& smoothers = GetSet<SmoothMovement>();
	auto& transforms = GetSet<demo::DemoTransformComponent>();

	const int32_t count = smoothers.GetCount();
	for (int32_t i = 0; i < count; ++i)
	{
		const int32_t index = smoothers.dense[i];
		auto& smoother = *smoothers[i];
		auto& transform = *transforms[index];

		const float xDelta = smoother.xDir * smoother.movementSpeed * deltaTime;
		const float yDelta = smoother.yDir * smoother.movementSpeed * deltaTime;

		transform.x += xDelta;
		transform.y += yDelta;

		const bool rotate = abs(xDelta) > 0 || abs(yDelta) > 0;
		if (!rotate)
			continue;
		
		float targetDegrees = atan2f(smoother.xDir, -smoother.yDir) * 180 / M_PI;
		if (targetDegrees < 0)
			targetDegrees += 360;

		const float currentDegrees = transform.degrees - floor(transform.degrees / 360) * 360;

		bool dir = currentDegrees > targetDegrees;
		const bool reverse = abs(currentDegrees - targetDegrees) < 180;
		if (reverse)
			dir = !dir;

		const float delta = smoother.rotationSpeed * (dir * 2 - 1) * deltaTime;
		transform.degrees = currentDegrees + delta;
	}
}

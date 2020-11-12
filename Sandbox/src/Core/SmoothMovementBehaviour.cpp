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

		const float degrees = atan2(smoother.xDir, -smoother.yDir) * 180 / M_PI;
		transform.degrees = degrees;
	}
}

#include "Demo/ComponentSystems/CameraSystem.h"
#include "cECSar/ECSystemManager.h"
#include "Demo/Components/CameraComponent.h"
#include "Demo/Modules/RenderModule.h"
#include "Demo/Components/TransformComponent.h"
#include "Gamejam/Core/App.hpp"
#include <Demo\Components\CameraTargetComponent.h>
#include "Demo/Modules/TimeModule.h"

void jam::demo::CameraSystem::Update(cecsar::ECSystemManager& systemManager)
{
	auto& targets = systemManager.GetMapSet<CameraTargetComponent>();
	auto& transforms = systemManager.GetSparseSet<TransformComponent>();
	auto& cameras = systemManager.GetMapSet<CameraComponent>();

	auto& renderModule = systemManager.GetModule<RenderModule>();
	auto& timeModule = systemManager.GetModule<TimeModule>();
	auto& app = App::Get();

	// Find targets.
	float xTargetPos = 0;
	float yTargetPos = 0;

	for (auto& keyPair : targets)
	{
		const int32_t index = keyPair.first;
		auto& target = keyPair.second;
		auto& transform = transforms.instances[index];

		xTargetPos += transform.xPosGlobal + target.xOffset;
		yTargetPos += transform.yPosGlobal + target.yOffset;
	}

	const int32_t targetsSize = targets.size();
	xTargetPos /= targetsSize;
	yTargetPos /= targetsSize;

	// Calculate cameras.
	const int32_t xOffset = app.m_width / 2;
	const int32_t yOffset = app.m_height / 2;

	const float deltaTime = timeModule.deltaTime;

	for (auto& keyPair : cameras)
	{
		const int32_t index = keyPair.first;
		auto& camera = keyPair.second;
		auto& transform = transforms.instances[index];

		renderModule.xCameraOffset = -xOffset + transform.xPosGlobal;
		renderModule.yCameraOffset = -yOffset + transform.yPosGlobal;

		renderModule.degrees = -transform.degreesGlobal + camera.degrees;
		renderModule.zoom = camera.zoom;

		const float xCameraOffset = transform.xPosGlobal - xTargetPos;
		const float yCameraOffset = transform.yPosGlobal - yTargetPos;

		const float xCameraOffsetAbs = abs(xCameraOffset);
		const float yCameraOffsetAbs = abs(yCameraOffset);

		const int32_t xDir = xCameraOffset < 0 ? 1 : -1;
		const float xWarpModifier = (xCameraOffsetAbs - camera.xWarpThreshold) * xDir;

		const int32_t yDir = yCameraOffset < 0 ? 1 : -1;
		const float yWarpModifier = (yCameraOffsetAbs - camera.yWarpThreshold) * yDir;

		if (xCameraOffsetAbs > camera.xWarpThreshold)
			transform.xPos += xWarpModifier;
		else if (xCameraOffsetAbs > camera.xFollowThreshold)
		{
			const int32_t dir = (xCameraOffset < 0) * 2 - 1;
			const float offset = xCameraOffsetAbs - camera.xFollowThreshold;
			const float lerp = offset / (camera.xWarpThreshold - camera.xFollowThreshold);
			const float addedSpeed = (camera.maxFollowSpeed - camera.minFollowSpeed) * lerp;
			const float speed = camera.minFollowSpeed + addedSpeed * lerp;
			transform.xPos += speed * deltaTime * dir;
		}

		if (yCameraOffsetAbs > camera.yWarpThreshold)
			transform.yPos += yWarpModifier;
		else if (yCameraOffsetAbs > camera.yFollowThreshold)
		{
			const int32_t dir = (yCameraOffset < 0) * 2 - 1;
			const float offset = yCameraOffsetAbs - camera.yFollowThreshold;
			const float lerp = offset / (camera.yWarpThreshold - camera.yFollowThreshold);
			const float addedSpeed = (camera.maxFollowSpeed - camera.minFollowSpeed) * lerp;
			const float speed = camera.minFollowSpeed + addedSpeed * lerp;
			transform.yPos += speed * deltaTime * dir;
		}
	}
}

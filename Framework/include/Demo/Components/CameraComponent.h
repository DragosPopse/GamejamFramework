#pragma once

namespace jam::demo
{
	class CameraComponent final
	{
	public:
		float xOffset = 0;
		float yOffset = 0;

		float zoom = 2;
		float degrees = 0;

		float xFollowThreshold = 20;
		float yFollowThreshold = 20;

		float xWarpThreshold = 50;
		float yWarpThreshold = 50;

		float minFollowSpeed = 20;
		float maxFollowSpeed = 40;
	};
}
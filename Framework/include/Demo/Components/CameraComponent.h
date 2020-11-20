#pragma once

namespace jam::demo
{
	class CameraComponent final
	{
	public:
		float xOffset = 0;
		float yOffset = 0;

		float zoom = 6;
		float degrees = 0;

		float xFollowThreshold = 10;
		float yFollowThreshold = 10;

		float xWarpThreshold = 20;
		float yWarpThreshold = 20;

		float minFollowSpeed = 20;
		float maxFollowSpeed = 40;
	};
}
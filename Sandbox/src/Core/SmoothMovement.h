#pragma once

namespace jam
{
	class SmoothMovement final
	{
	public:
		float xDir = 0;
		float yDir = 0;

		float rotationSpeed = 1;
		float movementSpeed = 50;
	};
}
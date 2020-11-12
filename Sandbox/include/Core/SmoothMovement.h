#pragma once

namespace jam
{
	class SmoothMovement final
	{
	public:
		float xDir = 0;
		float yDir = 0;

		float rotationSpeed = 500;
		float movementSpeed = 100;
	};
}
#include <Gamejam/Demo/DemoControllerBehaviour.h>
#include "Gamejam/Demo/DemoTransformComponent.h"
#include "SDL.h"

jam::demo::DemoControllerBehaviour::DemoControllerBehaviour(jecs::SystemManager& manager) :
	ISystemBehaviour<DemoControllerComponent>(manager)
{

}

void jam::demo::DemoControllerBehaviour::Update(const float deltaTime)
{
	/*
	The goal is to move entities that have a controller based on the player's input.
	We assume that those entities have transform components.
	*/

	// Get all controller and transform entities. Make sure it's a reference.
	auto& controllers = GetSet<DemoControllerComponent>();
	auto& transforms = GetSet<DemoTransformComponent>();

	// We only need to check the input once. This is one of the major advantages of using ECS.
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	float xDir = 0, yDir = 0;

	if (state[SDL_SCANCODE_W])
		yDir -= 1;
	if (state[SDL_SCANCODE_A])
		xDir -= 1;
	if (state[SDL_SCANCODE_S])
		yDir += 1;
	if (state[SDL_SCANCODE_D])
		xDir += 1;

	// Same with deltatime. Why do the same calculation multiple times?
	xDir *= deltaTime;
	yDir *= deltaTime;

	// Iterate over controllers and update the transforms.
	const int32_t count = controllers.GetCount();
	for (int32_t i = 0; i < count; ++i)
	{
		// Copying components is usually fine because they're small.
		// Just make sure you're editing the original instance when modifying stuff.

		const int32_t index = controllers.dense[i];
		const DemoControllerComponent controller = *controllers[i];
		DemoTransformComponent& transform = transforms.instances[index];

		transform.x += xDir * controller.speed;
		transform.y += yDir * controller.speed;
	}
}

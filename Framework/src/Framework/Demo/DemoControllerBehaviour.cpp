#include <Gamejam/Demo/DemoControllerBehaviour.h>
#include "Gamejam/Demo/DemoTransformComponent.h"
#include "SDL.h"

jam::demo::DemoControllerBehaviour::DemoControllerBehaviour(jecs::SystemManager& manager) :
	ISystemBehaviour<DemoControllerComponent>(manager)
{

}

void jam::demo::DemoControllerBehaviour::Update(const float deltaTime)
{
	auto& controllers = GetSet<DemoControllerComponent>();
	auto& transforms = GetSet<DemoTransformComponent>();

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

	xDir *= deltaTime;
	yDir *= deltaTime;

	const int32_t count = controllers.GetCount();
	for (int32_t i = 0; i < count; ++i)
	{
		const int32_t index = controllers.dense[i];
		const DemoControllerComponent controller = *controllers[i];
		DemoTransformComponent& transform = transforms.instances[index];

		transform.x += xDir * controller.speed;
		transform.y += yDir * controller.speed;
	}
}

#include "Demo/ComponentSystems/PlayerInputSystem.h"
#include "cECSar/ECSystemManager.h"
#include "Demo/Components/PlayerInputComponent.h"
#include "SDL.h"
#include "Demo/Components/ControllerComponent.h"

void jam::demo::PlayerInputSystem::Update(cecsar::ECSystemManager& systemManager)
{
	auto& inputComponents = systemManager.GetSparseSet<PlayerInputComponent>();
	auto& controllers = systemManager.GetSparseSet<ControllerComponent>();

	const int32_t count = inputComponents.GetCount();
	const auto updatedController = GetUpdatedController();

	for (int32_t i = 0; i < count; ++i)
	{
		const int32_t index = inputComponents.dense[i];
		controllers.instances[index] = updatedController;
	}
}

jam::demo::ControllerComponent jam::demo::PlayerInputSystem::GetUpdatedController()
{
	ControllerComponent controller;

	const Uint8* state = SDL_GetKeyboardState(nullptr);

	controller.xDir = state[SDL_SCANCODE_D] - state[SDL_SCANCODE_A];
	controller.yDir = state[SDL_SCANCODE_S] - state[SDL_SCANCODE_W];

	SDL_GetMouseState(&controller.xMouse, &controller.yMouse);
	controller.lMouse = state[SDL_BUTTON_LEFT];
	controller.rMouse = state[SDL_BUTTON_RIGHT];

	controller.space = state[SDL_SCANCODE_SPACE];

	return controller;
}

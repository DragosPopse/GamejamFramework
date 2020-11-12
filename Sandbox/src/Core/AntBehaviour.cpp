#include "Core/AntBehaviour.h"
#include "Core/SmoothMovement.h"
#include "SDL.h"

jam::AntBehaviour::AntBehaviour(jecs::SystemManager& manager) :
	ISystemBehaviour<AntBrain>(manager)
{

}

void jam::AntBehaviour::Update()
{
	auto& antBrains = GetSet<AntBrain>();
	auto& smootMovement = GetSet<SmoothMovement>();

	const Uint8* state = SDL_GetKeyboardState(nullptr);
	int32_t xDir = 0, yDir = 0;

	if (state[SDL_SCANCODE_W])
		yDir -= 1;
	if (state[SDL_SCANCODE_A])
		xDir -= 1;
	if (state[SDL_SCANCODE_S])
		yDir += 1;
	if (state[SDL_SCANCODE_D])
		xDir += 1;

	const int32_t count = antBrains.GetCount();
	for (int32_t i = 0; i < count; ++i)
	{
		const int32_t index = antBrains.dense[i];
		auto& movementInstance = smootMovement.instances[index];

		movementInstance.xDir = xDir;
		movementInstance.yDir = yDir;
	}
}

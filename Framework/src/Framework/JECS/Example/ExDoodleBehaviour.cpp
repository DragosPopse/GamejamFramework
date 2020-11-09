#include "ExDoodleBehaviour.h"

jam::jecs::Examples::ExDoodleBehaviour::ExDoodleBehaviour(SystemManager& manager) :
	ISystemBehaviour<ExDoodleBrain>(manager)
{
}

void jam::jecs::Examples::ExDoodleBehaviour::Update(
	Doodles doodles, Transforms transforms, Renderers renderers,
	const float deltaTime, const float time) const
{
	float xDir = 0, yDir = 0;

	const Uint8* state = SDL_GetKeyboardState(nullptr);

	if (state[SDL_SCANCODE_W])
		yDir -= 1;
	if (state[SDL_SCANCODE_A])
		xDir -= 1;
	if (state[SDL_SCANCODE_S])
		yDir += 1;
	if (state[SDL_SCANCODE_D])
		xDir += 1;

	const int32_t count = doodles.GetCount();
	for (int32_t i = 0; i < count; ++i)
	{
		const auto index = doodles.dense[i];
		auto& doodle = *doodles[i];
		auto& transform = transforms.instances[index];
		auto& renderer = renderers.instances[index];

		transform.x += xDir * deltaTime * 100 * doodle.moveSpeed;
		transform.y += yDir * deltaTime * 100 * doodle.moveSpeed;

		renderer.scale = 1 + abs(sin(time * doodle.jumpSpeed + .2) * 5);
	}
}

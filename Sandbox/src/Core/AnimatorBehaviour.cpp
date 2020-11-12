#include "Core/AnimatorBehaviour.h"
#include "Gamejam/Demo/Components/DemoRenderComponent.h"

jam::AnimatorBehaviour::AnimatorBehaviour(jecs::SystemManager& manager) :
	ISystemBehaviour<AnimatorComponent>(manager)
{

}

void jam::AnimatorBehaviour::Update(const float deltaTime)
{
	auto& animators = GetSet<AnimatorComponent>();
	auto& renderers = GetSet<demo::DemoRenderComponent>();

	const int32_t count = animators.GetCount();
	for (int32_t i = 0; i < count; ++i)
	{
		const int32_t index = animators.dense[i];
		auto& animator = *animators[i];
		auto& renderer = renderers.instances[index];

		const int32_t from = animator.from;
		int32_t to = animator.to;
		if (to == -1)
			to = renderer.count;

		animator.lerp += animator.speed * deltaTime;
		if (animator.lerp > 1)
			animator.lerp = !animator.loop;

		const int32_t frame = from + to * animator.lerp;
		renderer.index = frame;
	}
}

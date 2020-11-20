#include "Demo/ComponentSystems/AnimatorSystem.h"
#include "cECSar/ECSystemManager.h"
#include "Demo/Components/AnimatorComponent.h"
#include "Demo/Components/RenderComponent.h"
#include "Demo/Modules/TimeModule.h"

void jam::demo::AnimatorSystem::Update(cecsar::ECSystemManager& systemManager)
{
	auto& animators = systemManager.GetSet<AnimatorComponent>();
	auto& renderers = systemManager.GetSet<RenderComponent>();

	auto& timeModule = systemManager.GetModule<TimeModule>();
	const float deltaTime = timeModule.deltaTime;

	const int32_t count = animators.GetCount();
	for (int32_t i = 0; i < count; ++i)
	{
		const int32_t index = animators.dense[i];
		auto& animator = animators.instances[index];
		auto& renderer = renderers.instances[index];

		animator.m_lerp += deltaTime;
		if (animator.m_lerp > 1)
			animator.m_lerp = 0;

		const int32_t to = (animator.to == -1 ? renderer.count : animator.to) - animator.from;
		renderer.index = animator.from + to * animator.m_lerp;
	}
}

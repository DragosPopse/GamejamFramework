#include "..\..\include\Core\GravityBehaviour.h"
#include "..\..\Framework\include\Gamejam\Demo\Components\DemoTransformComponent.h"

jam::GravityBehaviour::GravityBehaviour(jecs::SystemManager& manager) :
	ISystemBehaviour<GravityComponent>(manager)
{

}

void jam::GravityBehaviour::Update(float deltaTime)
{
	auto& gravityComponents = GetSet<GravityComponent>();
	auto& transformComponents = GetSet<jam::demo::DemoTransformComponent>();

	const int32_t count = gravityComponents.GetCount();
	for (int32_t i = 0; i < count; ++i)
	{
		const int32_t index = gravityComponents.dense[i];

		auto gravityComponent = gravityComponents[i];

		transformComponents.instances[index].y += gravityComponent->gravity * deltaTime;
		
	}
}

#include "Demo/Factories/DoodleFactory.h"
#include "cECSar/ECSystemManager.h"
#include "Demo/Components/TransformComponent.h"
#include "Demo/Components/RenderComponent.h"
#include "Demo/Modules/RenderModule.h"

void jam::demo::DoodleFactory::OnConstruction(cecsar::ECSystemManager& manager, const int32_t index)
{
	auto& transform = manager.AddComponent<TransformComponent>(index);
	transform.x = rand() % 600;
	transform.y = rand() % 400;

	auto& renderer = manager.AddComponent<RenderComponent>(index);
	renderer.texture = manager.GetModule<RenderModule>().GetTexture("Art/doodle.png");
}

#include "Demo/Factories/WallFactory.h"
#include "cECSar/ECSystemManager.h"
#include "Demo/Components/TransformComponent.h"
#include "Demo/Components/RenderComponent.h"
#include "Demo/Modules/RenderModule.h"

void jam::demo::WallFactory::OnConstruction(
	cecsar::ECSystemManager& manager, const int32_t index)
{
	manager.AddComponent<TransformComponent>(index);
	auto& renderer = manager.AddComponent<RenderComponent>(index);

	auto& module = manager.GetModule<RenderModule>();
	renderer.texture = module.GetTexture("files/Wall.png");
}

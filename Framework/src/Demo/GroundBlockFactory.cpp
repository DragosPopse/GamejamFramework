#include "Demo/Factories/GroundBlockFactory.h"
#include "cECSar/ECSystemManager.h"
#include "Demo/Components/TransformComponent.h"
#include "Demo/Components/RenderComponent.h"
#include "Demo/Modules/RenderModule.h"

void jam::demo::GroundBlockFactory::OnConstruction(
	cecsar::ECSystemManager& manager, const int32_t index)
{
	manager.AddSparseComponent<TransformComponent>(index);
	auto& renderer = manager.AddSparseComponent<RenderComponent>(index);
	renderer.texture = manager.GetModule<RenderModule>().GetTexture("files/Spritesheet.png");
	renderer.count = 15;
	renderer.index = 3;
}

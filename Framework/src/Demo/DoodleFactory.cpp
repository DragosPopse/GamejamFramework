#include "Demo/Factories/DoodleFactory.h"
#include "cECSar/ECSystemManager.h"
#include "Demo/Components/TransformComponent.h"
#include "Demo/Components/RenderComponent.h"
#include "Demo/Modules/RenderModule.h"

jam::demo::DoodleFactory::DoodleFactory(cecsar::ECSystemManager& manager) :
	IEntityFactory(manager)
{
}

void jam::demo::DoodleFactory::OnConstruction(cecsar::ECSystemManager& manager, const int32_t index)
{
	auto& transform = manager.AddComponent<TransformComponent>(index);
	transform.m_x = rand() % 600;
	transform.m_y = rand() % 400;

	auto& renderer = manager.AddComponent<RenderComponent>(index);
	renderer.m_texture = manager.GetModule<RenderModule>().GetTexture("Art/doodle.png");
}

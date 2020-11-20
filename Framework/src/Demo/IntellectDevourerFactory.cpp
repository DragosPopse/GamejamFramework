#include "Demo/Factories/IntellectDevourerFactory.h"
#include "cECSar/ECSystemManager.h"
#include "Demo/Components/TransformComponent.h"
#include "Demo/Components/RenderComponent.h"
#include "Demo/Modules/RenderModule.h"
#include "Demo/Components/ControllerComponent.h"
#include "Demo/Components/PlayerInputComponent.h"
#include "Demo/Components/MovementComponent.h"
#include "Demo/Components/CameraTargetComponent.h"

void jam::demo::IntellectDevourerFactory::OnConstruction(
	cecsar::ECSystemManager& manager, const int32_t index)
{
	manager.AddComponent<TransformComponent>(index);
	manager.AddComponent<MovementComponent>(index);
	manager.AddComponentSmall<CameraTargetComponent>(index);

	manager.AddComponent<ControllerComponent>(index);
	manager.AddComponent<PlayerInputComponent>(index);

	auto& renderer = manager.AddComponent<RenderComponent>(index);
	renderer.texture = manager.GetModule<RenderModule>().GetTexture("files/IntellectDevourer.png");
	renderer.count = 4;
}

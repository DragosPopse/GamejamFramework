#include "Demo/Factories/IntellectDevourerFactory.h"
#include "cECSar/ECSystemManager.h"
#include "Demo/Components/TransformComponent.h"
#include "Demo/Components/RenderComponent.h"
#include "Demo/Modules/RenderModule.h"
#include "Demo/Components/ControllerComponent.h"
#include "Demo/Components/PlayerInputComponent.h"
#include "Demo/Components/MovementComponent.h"
#include "Demo/Components/CameraTargetComponent.h"
#include "Demo/Components/AnimatorComponent.h"

void jam::demo::IntellectDevourerFactory::OnConstruction(
	cecsar::ECSystemManager& manager, const int32_t index)
{
	manager.AddSparseComponent<TransformComponent>(index);
	manager.AddSparseComponent<MovementComponent>(index);
	manager.AddMapComponent<CameraTargetComponent>(index);

	manager.AddSparseComponent<ControllerComponent>(index);
	manager.AddSparseComponent<PlayerInputComponent>(index);

	auto& renderer = manager.AddSparseComponent<RenderComponent>(index);
	renderer.texture = manager.GetModule<RenderModule>().GetTexture("files/IntellectDevourer.png");
	renderer.count = 4;

	auto& animator = manager.AddSparseComponent<AnimatorComponent>(index);
	animator.to = 2;
}

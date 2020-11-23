#include "Demo/Factories/BatFactory.h"
#include "cECSar/ECSystemManager.h"
#include "Demo/Components/TransformComponent.h"
#include "Demo/Components/RenderComponent.h"
#include "Demo/Modules/RenderModule.h"
#include "Demo/Components/MovementComponent.h"
#include "Demo/Components/ControllerComponent.h"
#include "Demo/Components/BatComponent.h"
#include "Demo/Components/AnimatorComponent.h"

void jam::demo::BatFactory::OnConstruction(cecsar::ECSystemManager& manager, int32_t index)
{
	manager.AddSparseComponent<TransformComponent>(index);

	auto& renderer = manager.AddSparseComponent<RenderComponent>(index);
	renderer.texture = manager.GetModule<RenderModule>().GetTexture("files/Bat.png");
	renderer.count = 2;

	manager.AddSparseComponent<AnimatorComponent>(index);

	auto& movement = manager.AddSparseComponent<MovementComponent>(index);
	movement.movementSpeed /= 2;
	movement.rotationSpeed /= 4;

	manager.AddSparseComponent<ControllerComponent>(index);
	manager.AddSparseComponent<BatComponent>(index);
}

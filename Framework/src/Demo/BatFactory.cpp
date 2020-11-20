#include "Demo/Factories/BatFactory.h"
#include "cECSar/ECSystemManager.h"
#include "Demo/Components/TransformComponent.h"
#include "Demo/Components/RenderComponent.h"
#include "Demo/Modules/RenderModule.h"
#include "Demo/Components/MovementComponent.h"
#include "Demo/Components/ControllerComponent.h"
#include "Demo/Components/BatComponent.h"

void jam::demo::BatFactory::OnConstruction(cecsar::ECSystemManager& manager, int32_t index)
{
	manager.AddComponent<TransformComponent>(index);

	auto& renderer = manager.AddComponent<RenderComponent>(index);
	renderer.texture = manager.GetModule<RenderModule>().GetTexture("files/Bat.png");
	renderer.count = 2;

	auto& movement = manager.AddComponent<MovementComponent>(index);
	movement.movementSpeed /= 2;
	movement.rotationSpeed /= 4;

	manager.AddComponent<ControllerComponent>(index);
	manager.AddComponent<BatComponent>(index);
}

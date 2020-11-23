#include "Demo/Factories/PlayerCameraFactory.h"
#include "cECSar/ECSystemManager.h"
#include "Demo/Components/CameraComponent.h"
#include "Demo/Components/TransformComponent.h"

void jam::demo::PlayerCameraFactory::OnConstruction(
	cecsar::ECSystemManager& manager, const int32_t index)
{
	manager.AddSparseComponent<TransformComponent>(index);
	manager.AddMapComponent<CameraComponent>(index);
}

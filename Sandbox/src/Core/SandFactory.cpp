#include "Gamejam/Demo/Components/DemoTransformComponent.h"
#include "Gamejam/Demo/Components/DemoRenderComponent.h"
#include "Gamejam/Demo/Components/DemoCollisionComponent.h"
#include "Gamejam/Demo/Other/DemoTextureLib.h"
#include "Core/SandBrain.h"
#include "Core/SandFactory.h"

jam::SandFactory::SandFactory(jecs::SystemManager& manager) : EntityFactory(manager)
{
}

void jam::SandFactory::OnConstruction()
{
	Add<SandBrain>();

	auto& renderer = Add<demo::DemoRenderComponent>();
	Add<demo::DemoTransformComponent>();

	auto& collider = Add<demo::DemoCollisionComponent>();
	collider.isStatic = true;

	auto& lib = demo::DemoTextureLib::Get();
	renderer.texture = lib.GetTexture("files/tileSheet.png");
	renderer.count = 3;
	renderer.index = 2;
	renderer.scale = 1.0 / 8;
}

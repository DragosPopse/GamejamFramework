#include "..\..\include\Core\SandFactory.h"
#include "Core/AntFactory.h"
#include "Gamejam/Demo/Components/DemoTransformComponent.h"
#include "Gamejam/Demo/Components/DemoRenderComponent.h"
#include "Gamejam/Demo/Components/DemoCollisionComponent.h"
#include "Gamejam/Demo/Other/DemoTextureLib.h"
#include "Core/AntBrain.h"
#include "Core/SmoothMovement.h"
#include "Core/AnimatorComponent.h"

jam::SandFactory::SandFactory(jecs::SystemManager& manager) : EntityFactory(manager)
{
}

void jam::SandFactory::OnConstruction()
{
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

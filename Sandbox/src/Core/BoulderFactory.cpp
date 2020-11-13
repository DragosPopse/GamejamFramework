#include "..\..\include\Core\BoulderFactory.h"
#include "Core/AntFactory.h"
#include "Gamejam/Demo/Components/DemoTransformComponent.h"
#include "Gamejam/Demo/Components/DemoRenderComponent.h"
#include "Gamejam/Demo/Components/DemoCollisionComponent.h"
#include "Gamejam/Demo/Other/DemoTextureLib.h"
#include <Core\GravityComponent.h>

jam::BoulderFactory::BoulderFactory(jecs::SystemManager& manager) : EntityFactory(manager)
{
}

void jam::BoulderFactory::OnConstruction()
{
	auto& renderer = Add<demo::DemoRenderComponent>();
	Add<demo::DemoTransformComponent>();

	auto& collider = Add<demo::DemoCollisionComponent>();

	auto& gravity = Add<GravityComponent>();

	auto& lib = demo::DemoTextureLib::Get();
	renderer.texture = lib.GetTexture("files/boulder.png");
	renderer.count = 1;
	renderer.index = 0;
	renderer.scale = 1.0 / 8;
}
﻿#include "Gamejam/Demo/Other/DemoTextureLib.h"
#include "Gamejam/Demo/Components/DemoRenderComponent.h"
#include "Gamejam/Demo/Factories/DemoDummyFactory.h"
#include "Gamejam/Demo/Components/DemoTransformComponent.h"

jam::demo::DemoDummyFactory::DemoDummyFactory(jecs::SystemManager& manager) :
	EntityFactory(manager)
{

}

void jam::demo::DemoDummyFactory::OnConstruction()
{
	// Add the components you want, and setup some stuff like textures and position.

	DemoTransformComponent& transform = Add<DemoTransformComponent>();
	transform.x = rand() % 600;
	transform.y = rand() % 400;

	DemoRenderComponent& renderer = Add<jam::demo::DemoRenderComponent>();
	renderer.texture = jam::demo::DemoTextureLib::Get().GetTexture("Art/Doodle.png");
}

﻿#include "Core/AntFactory.h"
#include "Gamejam/Demo/Components/DemoTransformComponent.h"
#include "Gamejam/Demo/Components/DemoRenderComponent.h"
#include "Gamejam/Demo/Components/DemoCollisionComponent.h"
#include "Gamejam/Demo/Other/DemoTextureLib.h"
#include "Core/AntBrain.h"
#include "Core/SmoothMovement.h"

jam::AntFactory::AntFactory(jecs::SystemManager& manager) :
	EntityFactory(manager)
{

}

void jam::AntFactory::OnConstruction()
{
	Add<AntBrain>();
	Add<SmoothMovement>();

	Add<demo::DemoTransformComponent>();
	Add<demo::DemoCollisionComponent>();
	auto& renderer = Add<jam::demo::DemoRenderComponent>();

	auto& lib = demo::DemoTextureLib::Get();
	renderer.texture = lib.GetTexture("files/ant.png");
	renderer.scale = .2;
}

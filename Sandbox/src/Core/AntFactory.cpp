#include "Core/AntFactory.h"
#include "Gamejam/Demo/Components/DemoTransformComponent.h"
#include "Gamejam/Demo/Components/DemoRenderComponent.h"
#include "Gamejam/Demo/Components/DemoCollisionComponent.h"
#include "Gamejam/Demo/Other/DemoTextureLib.h"
#include "Core/AntBrain.h"
#include "Core/SmoothMovement.h"

void demo::AntFactory::OnConstruction()
{
	Add<jam::AntBrain>();
	Add<jam::SmoothMovement>();

	Add<jam::demo::DemoTransformComponent>();
	auto& renderer = Add<jam::demo::DemoRenderComponent>();
	Add<jam::demo::DemoCollisionComponent>();

	auto& lib = jam::demo::DemoTextureLib::Get();
	renderer.texture = lib.GetTexture("files/ant.png");
}

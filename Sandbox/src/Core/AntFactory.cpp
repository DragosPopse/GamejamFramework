#include "Core/AntFactory.h"
#include "Gamejam/Demo/Components/DemoTransformComponent.h"
#include "Gamejam/Demo/Components/DemoRenderComponent.h"
#include "Gamejam/Demo/Components/DemoCollisionComponent.h"
#include "Gamejam/Demo/Other/DemoTextureLib.h"
#include "Core/AntBrain.h"
#include "Core/SmoothMovement.h"
#include "Core/AnimatorComponent.h"
#include "Core/SandRemoverComponent.h"

jam::AntFactory::AntFactory(jecs::SystemManager& manager) :
	EntityFactory(manager)
{

}

void jam::AntFactory::OnConstruction()
{
	Add<AntBrain>();
	Add<SmoothMovement>();
	Add<SandRemoverComponent>();

	auto& animator = Add<AnimatorComponent>();
	animator.to = 3;
	animator.speed = 3;

	Add<demo::DemoTransformComponent>();
	Add<demo::DemoCollisionComponent>();
	auto& renderer = Add<demo::DemoRenderComponent>();
	renderer.count = 6;

	auto& lib = demo::DemoTextureLib::Get();
	renderer.texture = lib.GetTexture("files/ant_spritesheet.png");
	renderer.scale = 1.0 / 8;
}

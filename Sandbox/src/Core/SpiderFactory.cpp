#include "Core/SpiderFactory.h"
#include "Gamejam/Demo/Components/DemoTransformComponent.h"
#include "Gamejam/Demo/Components/DemoRenderComponent.h"
#include "Core/SmoothMovement.h"
#include "Gamejam/Demo/Components/DemoCollisionComponent.h"
#include "Gamejam/Demo/Other/DemoTextureLib.h"
#include "Core/AnimatorComponent.h"
#include <Core/SpiderBrain.h>

jam::SpiderFactory::SpiderFactory(jecs::SystemManager& manager) :
	EntityFactory(manager)
{
	
}

void jam::SpiderFactory::OnConstruction()
{
	Add<SpiderBrain>();
	Add<demo::DemoTransformComponent>();
	Add<demo::DemoCollisionComponent>();

	auto& smoother = Add<SmoothMovement>();
	smoother.movementSpeed /= 2;

	auto& renderer = Add<demo::DemoRenderComponent>();
	auto& lib = demo::DemoTextureLib::Get();
	renderer.texture = lib.GetTexture("files/spider.png");
	renderer.scale = 1.0 / 8;

	auto& animator = Add<AnimatorComponent>();
}

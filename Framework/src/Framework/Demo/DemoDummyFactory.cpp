#include "Gamejam/Demo/DemoDummyFactory.h"
#include "Gamejam/Demo/DemoTransformComponent.h"
#include "Gamejam/Demo/DemoRenderComponent.h"
#include "Gamejam/Demo/DemoTextureLib.h"

jam::demo::DemoDummyFactory::DemoDummyFactory(jecs::SystemManager& manager) :
	EntityFactory(manager)
{

}

void jam::demo::DemoDummyFactory::OnConstruction()
{
	DemoTransformComponent& transform = Add<DemoTransformComponent>();
	transform.x = rand() % 600;
	transform.y = rand() % 400;

	DemoRenderComponent& renderer = Add<DemoRenderComponent>();
	renderer.texture = DemoTextureLib::Get().GetTexture("Art/Doodle.png");
}

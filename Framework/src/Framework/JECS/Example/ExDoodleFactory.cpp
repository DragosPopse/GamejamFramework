#include "Gamejam/JECS/Examples/ExDoodleFactory.h"
#include "Gamejam/JECS/Examples/ExDoodleBrain.h"
#include "Gamejam/JECS/Examples/ExTransform.h"
#include "Gamejam/JECS/Examples/ExRenderer.h"
#include "Gamejam/JECS/Examples/ExRendererModule.h"

jam::jecs::Examples::ExDoodleFactory::ExDoodleFactory(SystemManager& manager, ExRendererModule& module) :
	EntityFactory(manager), _renderModule(&module)
{
}

void jam::jecs::Examples::ExDoodleFactory::OnConstruction()
{
	auto& doodleBrain = Add<ExDoodleBrain>();
	doodleBrain.moveSpeed = float(rand() % 5000) / 1000;
	doodleBrain.jumpSpeed = float(rand() % 5000) / 1000;

	auto& transform = Add<ExTransform>();
	transform.x = rand() % _renderModule->WIDTH;
	transform.y = rand() % _renderModule->WIDTH;

	auto& renderer = Add<ExRenderer>();
	renderer.texture = _renderModule->GetTexture(texturePath);
}

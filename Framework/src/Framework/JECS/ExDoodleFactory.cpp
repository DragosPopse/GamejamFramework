#include "ExDoodleFactory.h"
#include "ExTransform.h"
#include "ExRenderer.h"
#include "ExRendererModule.h"
#include "ExDoodleBrain.h"

jam::JECS::Examples::ExDoodleFactory::ExDoodleFactory(SystemManager& manager, ExRendererModule& module) :
	EntityFactory(manager), _renderModule(&module)
{
}

void jam::JECS::Examples::ExDoodleFactory::OnConstruction()
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

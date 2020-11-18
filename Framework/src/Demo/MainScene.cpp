#include "Demo/Scenes/MainScene.h"
#include "Demo/ComponentSystems/RenderSystem.h"
#include "Demo/Factories/DoodleFactory.h"

bool jam::demo::MainScene::Update(float dt)
{
	m_ecsManager.Update<RenderSystem>();
	return false;
}

bool jam::demo::MainScene::FixedUpdate(float dt)
{
	return false;
}

bool jam::demo::MainScene::Render()
{
	return false;
}

void jam::demo::MainScene::Enable()
{
	delete [] m_ecsManager.CreateFactoryEntities<DoodleFactory>(1000);
}

void jam::demo::MainScene::Disable()
{
	m_ecsManager.ClearEntities();
}

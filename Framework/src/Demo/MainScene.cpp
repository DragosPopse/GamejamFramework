#include "Demo/Scenes/MainScene.h"
#include "Demo/ComponentSystems/RenderSystem.h"
#include "Demo/Factories/DoodleFactory.h"
#include "Demo/Modules/RenderModule.h"

bool jam::demo::MainScene::Update(float dt)
{
	return false;
}

bool jam::demo::MainScene::FixedUpdate(float dt)
{
	return false;
}

bool jam::demo::MainScene::Render()
{
	m_ecsManager.GetModule<RenderModule>().PreRender();
	m_ecsManager.Update<RenderSystem>();
	m_ecsManager.GetModule<RenderModule>().PostRender();
	return false;
}

void jam::demo::MainScene::Enable()
{
	delete [] m_ecsManager.CreateFactoryEntities<DoodleFactory>(1000);
	m_ecsManager.GetModule<RenderModule>().m_zoom = 3;
}

void jam::demo::MainScene::Disable()
{
	m_ecsManager.ClearEntities();
}

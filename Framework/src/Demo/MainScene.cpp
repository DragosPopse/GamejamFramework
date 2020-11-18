#include "Demo/Scenes/MainScene.h"
#include "Demo/ComponentSystems/RenderSystem.h"
#include "Demo/Factories/DoodleFactory.h"
#include "Demo/Modules/RenderModule.h"
#include "Demo/ComponentSystems/TransformSystem.h"
#include "Demo/Components/TransformComponent.h"

bool jam::demo::MainScene::Update(float dt)
{
	m_ecsManager.GetSet<TransformComponent>().instances[3].xPos += dt * 20;
	m_ecsManager.GetSet<TransformComponent>().instances[1].yPos += dt * 20;
	m_ecsManager.GetSet<TransformComponent>().instances[1].degrees += dt * 10;
	m_ecsManager.GetSet<TransformComponent>().instances[2].yScale += dt / 3;
	m_ecsManager.GetSet<TransformComponent>().instances[2].depth += dt;

	m_ecsManager.Update<TransformSystem>();
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
	const int32_t count = 5;
	const auto indexes = m_ecsManager.CreateFactoryEntities<DoodleFactory>(count);
	m_ecsManager.GetSet<TransformComponent>().instances[1].parent = 3;
	m_ecsManager.GetSet<TransformComponent>().instances[1].xPos = 20;
	m_ecsManager.GetSet<TransformComponent>().instances[1].yPos = 30;

	m_ecsManager.GetSet<TransformComponent>().instances[2].parent = 1;
	m_ecsManager.GetSet<TransformComponent>().instances[2].xPos = -20;
	m_ecsManager.GetSet<TransformComponent>().instances[2].yPos = 40;
	delete [] indexes;
	m_ecsManager.GetModule<RenderModule>().zoom = .8;
	m_ecsManager.GetModule<RenderModule>().angle = 30;
}

void jam::demo::MainScene::Disable()
{
	m_ecsManager.ClearEntities();
}

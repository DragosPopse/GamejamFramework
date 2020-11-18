#include "Demo/Scenes/MainScene.h"
#include "Demo/ComponentSystems/RenderSystem.h"
#include "Demo/Factories/DoodleFactory.h"
#include "Demo/Modules/RenderModule.h"
#include "Demo/ComponentSystems/TransformSystem.h"
#include "Demo/Components/TransformComponent.h"

bool jam::demo::MainScene::Update(float dt)
{
	m_ecsManager.GetSet<TransformComponent>().m_instances[3].m_x += dt * 20;
	m_ecsManager.GetSet<TransformComponent>().m_instances[1].m_y += dt * 20;
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
	m_ecsManager.GetSet<TransformComponent>().m_instances[1].m_parent = 3;
	m_ecsManager.GetSet<TransformComponent>().m_instances[1].m_x = 20;
	m_ecsManager.GetSet<TransformComponent>().m_instances[1].m_y = 30;

	m_ecsManager.GetSet<TransformComponent>().m_instances[2].m_parent = 1;
	m_ecsManager.GetSet<TransformComponent>().m_instances[2].m_x = -20;
	m_ecsManager.GetSet<TransformComponent>().m_instances[2].m_y = 40;
	delete [] indexes;
	m_ecsManager.GetModule<RenderModule>().m_zoom = .8;
}

void jam::demo::MainScene::Disable()
{
	m_ecsManager.ClearEntities();
}

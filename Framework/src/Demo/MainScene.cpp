#include "Demo/Scenes/MainScene.h"
#include "Demo/ComponentSystems/RenderSystem.h"
#include "Demo/Modules/RenderModule.h"
#include "Demo/ComponentSystems/TransformSystem.h"
#include "Demo/Components/TransformComponent.h"
#include "Demo/Factories/GroundBlockFactory.h"

bool jam::demo::MainScene::Update(float dt)
{
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
	const int32_t groundBlockWidth = 30;
	const auto indexes = m_ecsManager.CreateFactoryEntities<GroundBlockFactory>(
		groundBlockWidth * groundBlockWidth);

	auto& transforms = m_ecsManager.GetSet<TransformComponent>();
	for (int32_t x = 0; x < groundBlockWidth; ++x)
		for (int32_t y = 0; y < groundBlockWidth; ++y)
		{
			const int32_t index = indexes[x + y * groundBlockWidth];
			auto& transform = transforms.instances[index];

			transform.xPos = x * 8;
			transform.yPos = y * 8;
		}
	
	delete [] indexes;

	auto& renderModule = m_ecsManager.GetModule<RenderModule>();
	renderModule.zoom = 2.6;
	renderModule.xOffset = 100;
	renderModule.yOffset = 300;
	renderModule.angle = 30;
}

void jam::demo::MainScene::Disable()
{
	m_ecsManager.ClearEntities();
}

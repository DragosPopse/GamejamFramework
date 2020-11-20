#include "Demo/Scenes/MainScene.h"
#include "Demo/ComponentSystems/RenderSystem.h"
#include "Demo/Modules/RenderModule.h"
#include "Demo/ComponentSystems/TransformSystem.h"
#include "Demo/Components/TransformComponent.h"
#include "Demo/Factories/GroundBlockFactory.h"
#include "Demo/Factories/IntellectDevourerFactory.h"
#include "Demo/Modules/TimeModule.h"
#include "Demo/ComponentSystems/PlayerInputSystem.h"
#include "Demo/ComponentSystems/MovementSystem.h"

bool jam::demo::MainScene::Update(const float dt)
{
	auto& timeModule = m_ecsManager.GetModule<TimeModule>();
	timeModule.deltaTime = dt * timeModule.timeScale;

	m_ecsManager.Update<PlayerInputSystem>();
	m_ecsManager.Update<MovementSystem>();
	m_ecsManager.Update<TransformSystem>();
	return false;
}

bool jam::demo::MainScene::FixedUpdate(const float dt)
{
	m_ecsManager.GetModule<TimeModule>().fixedDeltaTime = dt;

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

	const auto index = m_ecsManager.CreateFactoryEntities<IntellectDevourerFactory>(1);
	transforms.instances[index[0]].xPos = 100;
	transforms.instances[index[0]].yPos = 100;

	delete [] index;

	auto& renderModule = m_ecsManager.GetModule<RenderModule>();
	renderModule.zoom = 4.8;
	renderModule.xOffset = 900;
	renderModule.yOffset = 900;
	renderModule.angle = 0;
}

void jam::demo::MainScene::Disable()
{
	m_ecsManager.ClearEntities();
}

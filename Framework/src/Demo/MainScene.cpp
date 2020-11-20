﻿#include "Demo/Scenes/MainScene.h"
#include "Demo/ComponentSystems/RenderSystem.h"
#include "Demo/Modules/RenderModule.h"
#include "Demo/ComponentSystems/TransformSystem.h"
#include "Demo/Components/TransformComponent.h"
#include "Demo/Factories/GroundBlockFactory.h"
#include "Demo/Factories/IntellectDevourerFactory.h"
#include "Demo/Modules/TimeModule.h"
#include "Demo/ComponentSystems/PlayerInputSystem.h"
#include "Demo/ComponentSystems/MovementSystem.h"
#include "Demo/ComponentSystems/CameraSystem.h"
#include "Demo/Factories/PlayerCameraFactory.h"

bool jam::demo::MainScene::Update(const float dt)
{
	auto& timeModule = m_ecsManager.GetModule<TimeModule>();
	timeModule.deltaTime = dt * timeModule.timeScale;
	timeModule.time += timeModule.deltaTime;

	m_ecsManager.Update<PlayerInputSystem>();
	m_ecsManager.Update<MovementSystem>();
	m_ecsManager.Update<CameraSystem>();

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
	delete[] m_ecsManager.CreateFactoryEntities<PlayerCameraFactory>(1);

	const int32_t groundBlockWidth = 30;
	const auto indexes = m_ecsManager.CreateFactoryEntities<GroundBlockFactory>(
		groundBlockWidth * groundBlockWidth);

	auto& transforms = m_ecsManager.GetSet<TransformComponent>();
	auto& renderModule = m_ecsManager.GetModule<RenderModule>();

	for (int32_t x = 0; x < groundBlockWidth; ++x)
		for (int32_t y = 0; y < groundBlockWidth; ++y)
		{
			const int32_t index = indexes[x + y * groundBlockWidth];
			auto& transform = transforms.instances[index];

			transform.xPos = x * renderModule.spriteSize;
			transform.yPos = y * renderModule.spriteSize;
		}
	
	delete [] indexes;

	const auto index = m_ecsManager.CreateFactoryEntities<IntellectDevourerFactory>(1);
	transforms.instances[index[0]].xPos = 100;
	transforms.instances[index[0]].yPos = 100;

	delete [] index;
}

void jam::demo::MainScene::Disable()
{
	m_ecsManager.ClearEntities();
}

#include "Gamejam/Demo/DemoMainScene.h"
#include "Gamejam/Demo/DemoTransformComponent.h"
#include "Gamejam/Demo/DemoRenderComponent.h"
#include "SDL_image.h"
#include <Gamejam/Demo/DemoTextureLib.h>
#include <Gamejam/Demo/DemoDummyFactory.h>
#include "Gamejam/Demo/DemoControllerComponent.h"
#include "Gamejam/Demo/DemoControllerBehaviour.h"

jam::demo::DemoMainScene::DemoMainScene()
{
	m_systemManager = new jecs::SystemManager();

	// Add component types.
	m_systemManager->AddSystem<DemoTransformComponent>();
	m_systemManager->AddSystem<DemoRenderComponent>();
	m_systemManager->AddSystem<DemoControllerComponent>();

	// Add behaviours.
	m_renderBehaviour = new DemoRenderBehaviour(*m_systemManager);
	m_controllerBehaviour = new DemoControllerBehaviour(*m_systemManager);

	// Add factories.
	m_dummyFactory = new DemoDummyFactory(*m_systemManager);
}

jam::demo::DemoMainScene::~DemoMainScene()
{
	delete m_systemManager;
	delete m_renderBehaviour;
	delete m_controllerBehaviour;
	delete m_dummyFactory;
}

void jam::demo::DemoMainScene::Enable()
{
	for (int i = 0; i < 10; ++i)
		m_dummyFactory->Construct();

	const int32_t id = m_dummyFactory->Construct();
	m_systemManager->AddComponent<DemoControllerComponent>(id);
}
	

void jam::demo::DemoMainScene::Disable()
{
	DemoTextureLib::Get().Clear();
}

bool jam::demo::DemoMainScene::Update(const float deltaTime)
{
	m_controllerBehaviour->Update(deltaTime);
	return false;
}

bool jam::demo::DemoMainScene::Render()
{
	m_renderBehaviour->Update();
	return false;
}

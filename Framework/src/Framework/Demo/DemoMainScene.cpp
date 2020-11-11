#include "Gamejam/Demo/DemoMainScene.h"
#include "Gamejam/Demo/DemoTransformComponent.h"
#include "Gamejam/Demo/DemoRenderComponent.h"
#include "SDL_image.h"
#include <Gamejam/Demo/DemoTextureLib.h>
#include <Gamejam/Demo/DemoDummyFactory.h>

jam::demo::DemoMainScene::DemoMainScene()
{
	m_systemManager = new jecs::SystemManager();

	// Add component types.
	m_systemManager->AddSystem<DemoTransformComponent>();
	m_systemManager->AddSystem<DemoRenderComponent>();

	// Add behaviours.
	m_renderBehaviour = new DemoRenderBehaviour(*m_systemManager);

	// Add factories.
	m_dummyFactory = new DemoDummyFactory(*m_systemManager);
}

jam::demo::DemoMainScene::~DemoMainScene()
{
	delete m_systemManager;
	delete m_renderBehaviour;
	delete m_dummyFactory;
}

void jam::demo::DemoMainScene::Enable()
{
	m_dummyFactory->Construct();
}

void jam::demo::DemoMainScene::Disable()
{
	DemoTextureLib::Get().Clear();
}

bool jam::demo::DemoMainScene::Update(const float deltaTime)
{
	return false;
}

bool jam::demo::DemoMainScene::Render()
{
	m_renderBehaviour->Update();
	return false;
}

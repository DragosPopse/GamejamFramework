#include "Gamejam/Demo/DemoControllerBehaviour.h"
#include "Gamejam/Demo/Scenes/DemoMainScene.h"
#include "Gamejam/Demo/Factories/DemoDummyFactory.h"
#include "Gamejam/Demo/Behaviours/DemoRenderBehaviour.h"
#include "Gamejam/Demo/Components/DemoTransformComponent.h"
#include "Gamejam/Demo/Other/DemoTextureLib.h"
#include "Gamejam/Core/App.hpp"

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

	m_renderBehaviour->m_angle = 45;
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
	// Create the required entities.

	for (int i = 0; i < 5; ++i)
		m_dummyFactory->Construct();

	const int32_t id = m_dummyFactory->Construct();
	m_systemManager->AddComponent<DemoControllerComponent>(id);
}
	

void jam::demo::DemoMainScene::Disable()
{
	// Destroy all entities in the scene.

	m_systemManager->ClearEntities();
	DemoTextureLib::Get().Clear();
}

bool jam::demo::DemoMainScene::Update(const float deltaTime)
{
	// Update your behaviours.
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	if (state[SDL_SCANCODE_E]) {
		const auto ptr = std::make_shared<DemoMainScene>();
		ptr.get()->m_renderBehaviour->m_angle = 5;
		App::Get().m_manager.PushScene(ptr);
	}

	m_controllerBehaviour->Update(deltaTime);
	return false;
}

bool jam::demo::DemoMainScene::Render()
{
	// Update render related behaviours.

	m_renderBehaviour->Update();
	return true;
}

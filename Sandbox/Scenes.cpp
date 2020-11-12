#include <Core/Scenes.h>
#include "Gamejam/Demo/Scenes/DemoMainScene.h"
#include "Gamejam/Demo/Behaviours/DemoRenderBehaviour.h"
#include "Gamejam/Demo/Components/DemoTransformComponent.h"
#include "Gamejam/Core/App.hpp"
#include "Gamejam/Demo/Components/DemoCollisionComponent.h"
#include "Gamejam/Demo/Behaviours/DemoCollisionBehaviour.h"

using namespace jam::demo;

jam::MainScene::MainScene()
{
	m_systemManager = new jecs::SystemManager();

	// Add component types you're going to use.
	m_systemManager->AddSystem<DemoTransformComponent>();
	m_systemManager->AddSystem<DemoRenderComponent>();
	m_systemManager->AddSystem<DemoCollisionComponent>();

	// Add behaviours / game logic.
	m_renderBehaviour = new DemoRenderBehaviour(*m_systemManager);
	m_collisionBehaviour = new DemoCollisionBehaviour(*m_systemManager);

	// Add whatever other things you need.
}

jam::MainScene::~MainScene()
{
	delete m_systemManager;
	delete m_renderBehaviour;
	delete m_collisionBehaviour;
}

void jam::MainScene::Enable()
{
	// TODO ADD FACTORIES
}

void jam::MainScene::Disable()
{
	// Destroy all entities in the scene.
	m_systemManager->ClearEntities();
}

bool jam::MainScene::Update(const float deltaTime)
{
	// Update your behaviours.
	m_collisionBehaviour->Update();
	return false;
}

bool jam::MainScene::Render()
{
	// Update render related behaviours.
	SDL_Renderer* renderer = App::Get().m_renderer;
	TileMapper* tileMapper = TileMapper::GetInstance();
	SDL_RenderCopy(renderer, tileMapper->GetMap(), nullptr, nullptr);
	//m_renderBehaviour->Update();
	return false;
}

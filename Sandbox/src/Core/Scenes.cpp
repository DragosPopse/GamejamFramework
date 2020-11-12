#include <Core/Scenes.h>
#include "Gamejam/Demo/Scenes/DemoMainScene.h"
#include "Gamejam/Demo/Behaviours/DemoRenderBehaviour.h"
#include "Gamejam/Demo/Components/DemoTransformComponent.h"
#include "Gamejam/Core/App.hpp"
#include "Gamejam/Demo/Components/DemoCollisionComponent.h"
#include "Gamejam/Demo/Behaviours/DemoCollisionBehaviour.h"
#include "Core/AntFactory.h"
#include "Core/AntBrain.h"
#include "Core/SmoothMovement.h"
#include "Core/AntBehaviour.h"
#include "Core/SmoothMovementBehaviour.h"
#include "Core/AnimatorComponent.h"
#include "Core/AnimatorBehaviour.h"

using namespace jam::demo;

jam::MainScene::MainScene()
{
	m_systemManager = new jecs::SystemManager();

	// Add component types you're going to use.
	m_systemManager->AddSystem<DemoTransformComponent>();
	m_systemManager->AddSystem<DemoRenderComponent>();
	m_systemManager->AddSystem<DemoCollisionComponent>();

	// Game specific components.
	m_systemManager->AddSystem<AntBrain>();
	m_systemManager->AddSystem<SmoothMovement>();

	// Non framework utility components.
	m_systemManager->AddSystem<AnimatorComponent>();

	// Add behaviours / game logic.
	m_renderBehaviour = new DemoRenderBehaviour(*m_systemManager);
	m_collisionBehaviour = new DemoCollisionBehaviour(*m_systemManager);

	// Game specific behaviour.
	m_antBehaviour = new AntBehaviour(*m_systemManager);
	m_smoothMovementBehaviour = new SmoothMovementBehaviour(*m_systemManager);

	// Non framework utility behaviour.
	m_animatorBehaviour = new AnimatorBehaviour(*m_systemManager);

	// Add whatever other things you need.
}

jam::MainScene::~MainScene()
{
	delete m_systemManager;
	delete m_renderBehaviour;
	delete m_collisionBehaviour;

	delete m_antBehaviour;
	delete m_smoothMovementBehaviour;

	delete m_animatorBehaviour;
}

void jam::MainScene::Enable()
{
	// TODO ADD FACTORIES
	auto& set = m_systemManager->GetSet<DemoTransformComponent>();
	auto factory = AntFactory(*m_systemManager);
	for (int32_t i = 0; i < 100; ++i)
	{
		const int32_t id = factory.Construct();
		auto& transform = set.instances[id];
		transform.x = rand() % 600;
		transform.y = rand() % 400;
	}
}

void jam::MainScene::Disable()
{
	// Destroy all entities in the scene.
	m_systemManager->ClearEntities();
}

bool jam::MainScene::Update(const float deltaTime)
{
	// Update custom game behaviour.
	m_antBehaviour->Update();
	m_smoothMovementBehaviour->Update(deltaTime);

	// Update your behaviours.
	m_collisionBehaviour->Update();

	m_animatorBehaviour->Update(deltaTime);
	return false;
}

bool jam::MainScene::Render()
{
	// Update render related behaviours.
	SDL_Renderer* renderer = App::Get().m_renderer;
	TileMapper* tileMapper = TileMapper::GetInstance();
	SDL_RenderCopy(renderer, tileMapper->GetMap(), nullptr, nullptr);
	m_renderBehaviour->Update();
	return false;
}

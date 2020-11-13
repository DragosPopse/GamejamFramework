#include <Core/Scenes.h>
#include <sstream>
#include <fstream>
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
#include "Core/SandFactory.h"

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
	for (int32_t i = 0; i < 1; ++i)
	{
		const int32_t id = factory.Construct();
		auto& transform = set.instances[id];
		transform.x = rand() % 600;
		transform.y = rand() % 400;
	}

	// Add whatever other things you need.
	CreateEntities();
}

void jam::MainScene::Disable()
{
	// Destroy all entities in the scene.
	m_systemManager->ClearEntities();
}

void jam::MainScene::CreateEntities()
{
	vector<vector<int>> entities;
	std::ifstream entityMap("files/EntityMap.csv");

	if (!entityMap.is_open())
	{
		throw "Could not open file";
		exit(1);
	}

	string line;
	int val;
	bool firstLine = true;

	int rowIndx = 0;

	while (std::getline(entityMap, line, '#'))
	{
		std::stringstream ss(line);

		while (ss >> val)
		{
			if (rowIndx >= entities.size())
			{
				vector<int> row = vector<int>();
				entities.push_back(row);
			}

			entities[rowIndx].push_back(val);

			if (ss.peek() == ',') ss.ignore();
		}

		rowIndx++;
	}

	entityMap.close();

	auto& transforms = m_systemManager->GetSet<DemoTransformComponent>();
	for (int r = 0; r < entities.size(); r++)
	{
		for (int c = 0; c < entities[r].size(); c++)
		{
			int entityIndex = entities[r][c];

			if (entityIndex == 1)
			{

			}
			else if (entityIndex == 2)									//sand
			{
				auto sandFactory = SandFactory(*m_systemManager);
				auto index = sandFactory.Construct();
				transforms.instances[index].x = c * 32 + 16;
				transforms.instances[index].y = r * 32 + 16;
			}
		}
	}
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
	TileManager* tileManager = TileManager::GetInstance();
	SDL_RenderCopy(renderer, tileManager->GetMap(), nullptr, nullptr);
	m_renderBehaviour->Update();
	return false;
}

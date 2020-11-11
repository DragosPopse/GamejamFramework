#include "Gamejam/Demo/DemoMainScene.h"
#include "Gamejam/Demo/DemoTransformComponent.h"
#include "Gamejam/Demo/DemoRenderComponent.h"
#include "SDL_image.h"
#include "Gamejam/Core/App.hpp"

jam::demo::DemoMainScene::DemoMainScene()
{
	m_systemManager = new jecs::SystemManager();

	// Add component types.
	m_systemManager->AddSystem<DemoTransformComponent>();
	m_systemManager->AddSystem<DemoRenderComponent>();

	// Add behaviours.
	m_renderBehaviour = new DemoRenderBehaviour(*m_systemManager);

	m_systemManager->CreateEntity();
	m_systemManager->AddComponent<DemoTransformComponent>(0);
	m_systemManager->AddComponent<DemoRenderComponent>(0);

	m_systemManager->GetSet<DemoTransformComponent>()[0]->x = 100;
	m_systemManager->GetSet<DemoTransformComponent>()[0]->y = 100;

	m_systemManager->GetSet<DemoRenderComponent>()[0]->texture = &GetTexture("Art/Doodle.png");
}

jam::demo::DemoMainScene::~DemoMainScene()
{
	delete m_systemManager;
	delete m_renderBehaviour;
}

void jam::demo::DemoMainScene::Disable()
{
	for (const auto& texture : m_textureMap)
		SDL_DestroyTexture(texture.second);
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

SDL_Texture& jam::demo::DemoMainScene::GetTexture(const std::string key)
{
	const auto found = m_textureMap.find(key);
	if (found != m_textureMap.end())
		return *found->second;

	SDL_Surface* surface = IMG_Load(key.c_str());
	SDL_Renderer* renderer = App::Get().m_renderer;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
	return *texture;
}

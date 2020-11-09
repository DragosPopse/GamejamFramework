#include "ExampleEngine.h"
#include "SystemManager.h"
#include <SDL.h>
#include <ctime>
#include "ExRendererModule.h"
#include "ExTransform.h"
#include "ExRenderer.h"
#include "ExRendererBehaviour.h"
#include "ExDoodleBrain.h"
#include "ExDoodleBehaviour.h"
#include "ExDoodleFactory.h"
#include "SDL_image.h"

jam::JECS::Examples::ExampleEngine::~ExampleEngine()
{
	delete _manager;
	delete _renderModule;
	delete _rendererBehaviour;
	delete _doodleBehaviour;
}

void jam::JECS::Examples::ExampleEngine::Run()
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	SDL_SetHintWithPriority(SDL_HINT_RENDER_VSYNC, "0", SDL_HINT_OVERRIDE);

	// Setup deltatime.
	float previousTime = clock();
	SDL_Event event;

	float time = 0;

	Compile();
	Start();

	while (true)
	{
		while (SDL_PollEvent(&event) != 0)
			if (event.type == SDL_QUIT) 
				quit = true;
		if (quit)
			break;

		// Update deltatime.
		const float currentTime = clock();
		const float deltaTime = (currentTime - previousTime) * deltaScale * timeScale;

		time += deltaTime;
		previousTime = currentTime;

		Update(deltaTime, time);
	}

	SDL_Quit();
}

void jam::JECS::Examples::ExampleEngine::Compile()
{
	// Add core SystemManager.
	_manager = new SystemManager();

	// Add whatever external dependency you want.
	_renderModule = new ExRendererModule();

	// Add Component types you want to work with.
	_manager->AddSystem<ExTransform>();
	_manager->AddSystem<ExRenderer>();
	_manager->AddSystem<ExDoodleBrain>();

	// Add Behaviours and subscribe them to the corresponding systems.
	// I don't do this automatically since you might want to dynamically sub/unsub
	// behaviours during runtime.
	_rendererBehaviour = new ExRendererBehaviour(*_manager, *_renderModule);
	_doodleBehaviour = new ExDoodleBehaviour(*_manager);
}

void jam::JECS::Examples::ExampleEngine::Start() const
{
	ExDoodleFactory factory(*_manager, *_renderModule);
	for (int i = 0; i < 500; ++i)
		factory.Construct();
}

void jam::JECS::Examples::ExampleEngine::Update(const float deltaTime, const float time) const
{
	auto& doodles = _manager->GetSet<ExDoodleBrain>();
	auto& transforms = _manager->GetSet<ExTransform>();
	auto& renderers = _manager->GetSet<ExRenderer>();

	_doodleBehaviour->Update(doodles, transforms, renderers,
		deltaTime, time);

	// Rendering.
	_renderModule->PreRender();
	_rendererBehaviour->Update(renderers, transforms);
	_renderModule->PostRender();

	_renderModule->zoom = 1 - sin(time * 2) / 2;
	_renderModule->angle = cos(time) * 45;
}

#pragma once
#include "ExRendererBehaviour.h"
#include "ExDoodleBehaviour.h"

namespace DJ {
	namespace JECS {
		class SystemManager;
	}
}

namespace DJ
{
	namespace JECS 
	{
		namespace Examples
		{
			class ExRendererModule;

			class ExampleEngine
			{
			public:
				bool quit = false;
				float deltaScale = .001;
				float timeScale = 1;

				~ExampleEngine();
				void Run();

			private:
				SystemManager* _manager = nullptr;
				ExRendererModule* _renderModule = nullptr;
				ExRendererBehaviour* _rendererBehaviour = nullptr;
				ExDoodleBehaviour* _doodleBehaviour = nullptr;

				void Compile();
				void Start() const;
				void Update(float deltaTime, float time) const;
			};
		}
	}
}

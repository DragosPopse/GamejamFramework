#include "Gamejam/Core/Entry.hpp"
#include <SDL_vulkan.h>
#include "Gamejam/Core/App.hpp"
#include "Gamejam/SceneManagement/Scene.hpp"
#include "cECSar/ECSystemManager.h"


namespace jam
{
    class Application :
            public App
    {
    public:
        Application()
        {
            Info info;
            info.width = 32*20;
            info.height = 32*20;
            info.title = "Gamer";
            info.flags = SDL_WINDOW_SHOWN;
            info.fixedDelta = 1.f / 60.f;

            Init(info);
        }
    };

	class TimeModule : public cecsar::IModule
	{
	public:
		TimeModule(cecsar::ECSystemManager& manager) : IModule(manager)
		{
		}

		float dt = 1;
	};

	class ComponentA final
	{
	public:
		int32_t a = 0, b = 0;
	};

	class ComponentB final
	{
	public:
		int32_t c = 0, d = 0;
	};

	class ABFactory final : public cecsar::IEntityFactory
	{
	public:
		ABFactory(cecsar::ECSystemManager& manager)
			: IEntityFactory(manager)
		{
		}

		void OnConstruction(cecsar::ECSystemManager& manager, int32_t index) override
		{
			manager.AddComponent<ComponentA>(index);
			auto& component = manager.AddComponent<ComponentB>(index);
			component.c = 5;
		}
	};

	class ABComponentSystem : public cecsar::IComponentSystem
	{
	public:
		ABComponentSystem(cecsar::ECSystemManager& manager)
		{
			
		}

		void Update(cecsar::ECSystemManager& systemManager) override
		{
			auto& aSet = systemManager.GetSet<ComponentA>();
			auto& bSet = systemManager.GetSet<ComponentB>();

			const auto count = aSet.GetCount();
			for (int32_t i = 0; i < count; ++i)
			{
				const auto index = aSet.m_dense[i];
				auto& a = aSet.m_instances[index];
				auto& b = bSet.m_instances[index];

				a.b++;
				b.c--;
			}
		}
	};

	class MainScene final : public Scene
	{
	public:
		void Enable() override
		{
			delete [] manager.CreateFactoryEntities<ABFactory>(1000);
			manager.DestroyEntity(5);
			int32_t index = manager.CreateEntity();
		}

		void Disable() override
		{
			manager.ClearEntities();
		}

		bool Update(float dt) override
		{
			manager.GetModule<TimeModule>().dt = dt;
			manager.Update<ABComponentSystem>();
			return false;
		}

	private:
		cecsar::ECSystemManager manager = cecsar::ECSystemManager(1000);
	};
}

JAM_ENTRY_SCENE(jam::MainScene)
JAM_APP(jam::Application)
#pragma once
#include <Gamejam/Core/Config.hpp>
#include <Gamejam/JECS/Utilities/SparseSet.h>
#include <map>
#include <typeindex>
#include <unordered_set>
#include "JECSConsts.h"
#include "ComponentSystem.h"

/*
The SystemManager is the heart of this DOD/ECS system, and the only system you'll ever
need to interact with to make DOD/ECS work.

There are some other classes which I'll recommend using, but they're optional.

IT WORKS AS FOLLOWS:
- Create the SystemManager object.
- For every component type you want to use, call AddSystem<T>(), where T is your component type.
So for instance, AddComponent<Renderer>, AddComponent<Transform> etc etc.
You have to do this manually since it's pretty expensive to make this process automatic.

USING BEHAVIOURS (OPTIONAL):
- To create behaviour, inherit from ISystemBehaviour<T>, where T will be the main component type
the behaviour will handle. Multiple behaviours can be created for the same component.
- Subscribe/unsubscribe the behaviours at will with (un)SubscribeBehaviour<T>, where T is the
corresponding component.

NOT USING BEHAVIOURS:
You can not use behaviours, if you want to setup your own component behaviour systems.
Not recommended for people who just want to use the framework to get basic stuff going though.
- Use GetSet<T> to get the set you want, and you whatever you want to do with it.

USING ENTITY FACTORIES:
Entity factories help you define entities which you'll want to spawn often.
Read the comments in EntityFactory for more information.

NOT USING ENTITY FACTORIES:
- Use CreateEntity to spawn a new entity. The function returns the entity ID.
- Use AddComponent to add a component of your choosing, overloading the entity ID.
- Use RemoveComponent the same way.

CHECKING IF SOMETHING HAS COMPONENT T:
- GetSet<T>.Contains(id)

LOOK AT THE EXAMPLE PROJECT FOR A GREATER UNDERSTANDING.
*/

namespace jam
{
	namespace jecs
	{
		class SystemManager final
		{
		public:
			using Entity = std::unordered_set<std::type_index>;
			using EntityPool = Utilities::SparseSet<Entity>;

			~SystemManager();

			int32_t CreateEntity();
			void DestroyEntity(int32_t index);

			template <class T>
			ComponentSystem<T>& AddSystem();
			template <class T>
			ComponentSystem<T>& GetSystem();

			template <class T>
			void AddComponent(int32_t index);
			template <class T>
			void RemoveComponent(int32_t index);

			template <class T>
			Utilities::SparseSet<T>& GetSet();

		private:
			EntityPool _entities = EntityPool(ENTITY_CAPACITY);
			std::map<std::type_index, IComponentSystem*> _systems;
		};

		template <typename T>
		ComponentSystem<T>& SystemManager::AddSystem()
		{
			auto ptr = new ComponentSystem<T>(*this);
			_systems[typeid(T)] = ptr;
			return *ptr;
		}

		template <typename T>
		ComponentSystem<T>& SystemManager::GetSystem()
		{
			return *static_cast<ComponentSystem<T>*>(_systems[typeid(T)]);
		}

		template <typename T>
		void SystemManager::AddComponent(const int32_t index)
		{
			GetSystem<T>().OnAddComponent(index);

			auto entity = _entities.instances[index];
			entity.insert(typeid(T));
		}

		template <typename T>
		void SystemManager::RemoveComponent(int32_t index)
		{
			GetSystem<T>().OnRemoveComponent(index);

			auto entity = _entities.instances[index];
			entity.erase(typeid(T));
		}

		template <typename T>
		Utilities::SparseSet<T>& SystemManager::GetSet()
		{
			auto system = static_cast<ComponentSystem<T>*>(_systems[typeid(T)]);
			return system->GetSet();
		}
	}
}
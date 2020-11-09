#pragma once
#include <cstdint>
#include "SystemManager.h"
#include "ComponentSystem.h"

/*
The EntityFactory is ment to simplify object creation, 
and make it feel more like your classic, beloved OOP.

Creating an entity and manually adding it's components can be weird.
You don't really give the entity a name, and it's just a list of some components.

Sure, we can't name the entity itself, but we can name the building process.
So we get the MarioFactory, or the BulletFactory.
As the name suggest, it can create a specific entity automatically.

- HOW DO I USE IT?
1. Choose what entity type you want to automize making. Let's pick Mario for this example.
2. Create MarioFactory and inherit from EntityFactory.
3. In OnConstruction, use Add<T> to add the component types you want to your entity.
Add<T> even returns the created component! So you can modify some things if neccecary.

4. Call Construct to get yourself a new instance of Mario.
5. Destruction doesn't care what a entity called itself in life. 
So that can just be done in the SystemManager, like normal.
*/

namespace jam
{
	namespace jecs
	{
		class EntityFactory
		{
		public:
			EntityFactory(SystemManager& manager);
			virtual ~EntityFactory();

			int32_t Construct();

		protected:
			int32_t _index = NULL_OBJ;

			virtual void OnConstruction() = 0;
			template <typename T>
			T& Add();

		private:
			SystemManager& _manager;
		};

		template <typename T>
		T& EntityFactory::Add()
		{
			_manager.AddComponent<T>(_index);
			return _manager.GetSet<T>().instances[_index];
		}
	}
}
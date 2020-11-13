#pragma once
#include <Gamejam/Core/Config.hpp>
#include <Gamejam/JECS/Utilities/SparseSet.h>
#include "ComponentSystem.h"

/*
The ISystemBehaviour interface can be used to subscribe to
events in relation to componentSystems.

Not only that, but this interface allows you to easily
access the sets from each ComponentSystem.

- HOW DO I USE IT?
1. Inherit from ISystemBehaviour, choose a component type for T.
Let's use RenderComponent as an example.
2. You can inherit the various events like OnAddComponent to setup some stuff like checking
whether or not the target entity has a TransformComponent, and if not, adding one.
3. Use GetSet<U> to get any set. Pretty useful for a RenderComponent, where you also need access
to the TransformComponent.
*/

namespace jam
{
	namespace jecs
	{
		template <typename T>
		class ISystemBehaviour : public IComponentSystem
		{
		public:
			ISystemBehaviour(SystemManager& manager);
			virtual ~ISystemBehaviour();

		protected:
			template <typename U>
			Utilities::SparseSet<U>& GetSet();
			void RemoveEntity(int32_t index) const;

		private:
			SystemManager& _manager;
		};

		template <typename T>
		ISystemBehaviour<T>::ISystemBehaviour(SystemManager& manager) :
			_manager(manager)
		{
		}

		template <typename T>
		ISystemBehaviour<T>::~ISystemBehaviour() = default;

		template <typename T>
		template <typename U>
		Utilities::SparseSet<U>& ISystemBehaviour<T>::GetSet()
		{
			return _manager.GetSet<U>();
		}

		template <typename T>
		void ISystemBehaviour<T>::RemoveEntity(const int32_t index) const
		{
			_manager.DestroyEntity(index);
		}
	}
}
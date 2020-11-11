#pragma once
#include <Gamejam/Core/Config.hpp>
#include <Gamejam/JECS/Utilities/SparseSet.h>
#include <vector>
#include "JECSConsts.h"

namespace jam
{
	namespace jecs
	{
		class SystemManager;

		class IComponentSystem
		{
		public:
			virtual ~IComponentSystem();

			virtual void OnAddComponent(int32_t index);
			virtual void OnRemoveComponent(int32_t index);
		};

		template <typename T>
		class ComponentSystem final : public IComponentSystem
		{
		public:
			ComponentSystem(SystemManager& manager);

			void SubscribeBehaviour(IComponentSystem& behaviour);
			void UnsubscribeBehaviour(IComponentSystem& behaviour);

			void OnAddComponent(int32_t index) override;
			void OnRemoveComponent(int32_t index) override;

			Utilities::SparseSet<T>& GetSet();

		private:
			SystemManager& _manager;
			Utilities::SparseSet<T> _set = Utilities::SparseSet<T>(ENTITY_CAPACITY);
			std::vector<IComponentSystem*> _behaviours;
		};

		template <typename T>
		ComponentSystem<T>::ComponentSystem(SystemManager& manager) :
			_manager(manager)
		{

		}

		template <typename T>
		void ComponentSystem<T>::SubscribeBehaviour(IComponentSystem& behaviour)
		{
			_behaviours.push_back(&behaviour);
		}

		template <typename T>
		void ComponentSystem<T>::UnsubscribeBehaviour(IComponentSystem& behaviour)
		{
			const auto ptr = &behaviour;
			for (auto it = _behaviours.begin(); it != _behaviours.end(); ++it)
			{
				if (*it != ptr)
					continue;
				_behaviours.erase(it);
				return;
			}
		}

		template <typename T>
		void ComponentSystem<T>::OnAddComponent(const int32_t index)
		{
			_set.Add(index);
			for (IComponentSystem* behaviour : _behaviours)
				behaviour->OnAddComponent(index);
		}

		template <typename T>
		void ComponentSystem<T>::OnRemoveComponent(const int32_t index)
		{
			for (IComponentSystem* behaviour : _behaviours)
				behaviour->OnRemoveComponent(index);
			_set.Remove(index);
		}

		template <typename T>
		Utilities::SparseSet<T>& ComponentSystem<T>::GetSet()
		{
			return _set;
		}
	}
}
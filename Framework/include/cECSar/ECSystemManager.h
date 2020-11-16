#pragma once
#include <cstdint>
#include "SparseValueSet.h"
#include "Entity.h"
#include <unordered_map>
#include "ECSystem.h"
#include "IComponentSystem.h"

namespace jam::cecsar
{
	class IECSubscribeable;

	class ECSystemManager final
	{
	public:
		ECSystemManager(int32_t capacity);
		~ECSystemManager();

		// Entities.
		int32_t CreateEntity();
		void DestroyEntity(int32_t index);
		void ClearEntities();

		bool ContainsEntity(int32_t index, int32_t uniqueId=-1) const;
		int32_t GetEntityUniqueId(int32_t index) const;

		// Components.
		template <typename T>
		void AddComponent(int32_t index);
		template <typename T>
		void RemoveComponent(int32_t index);

		template <typename T>
		void Subscribe(IECSubscribeable& subscribeable);
		template <typename T>
		void Unsubscribe(IECSubscribeable& subscribeable);

		template <typename T>
		Utilities::SparseValueSet<T>& GetSet();

		// Systems.
		template <typename T>
		void Update();

	private:
		int32_t m_globalEntityIdIndex = 0;
		const int32_t m_capacity;

		Utilities::SparseValueSet<Entity>* m_entities;
		std::unordered_map<std::type_index, IECSystem*> m_systems;
		std::unordered_map<std::type_index, IComponentSystem*> m_componentSystems;

		template <typename T>
		ECSystem<T*>& GetSystem();
	};

	template <typename T>
	void ECSystemManager::AddComponent(const int32_t index)
	{
		GetSystem<T>().Add(index);
	}

	template <typename T>
	void ECSystemManager::RemoveComponent(const int32_t index)
	{
		GetSystem<T>().Remove(index);
	}

	template <typename T>
	void ECSystemManager::Subscribe(IECSubscribeable& subscribeable)
	{
		GetSystem<T>().Subscribe(subscribeable);
	}

	template <typename T>
	void ECSystemManager::Unsubscribe(IECSubscribeable& subscribeable)
	{
		GetSystem<T>().Unsubscribe(subscribeable);
	}

	template <typename T>
	Utilities::SparseValueSet<T>& ECSystemManager::GetSet()
	{
		return GetSystem<T>().m_set;
	}

	template <typename T>
	void ECSystemManager::Update()
	{
		if (m_componentSystems.count(typeid(T)) == 0)
			m_componentSystems[typeid(T)] = new T();
		m_componentSystems[typeid(T)]->Update(*this);
	}

	template <typename T>
	ECSystem<T*>& ECSystemManager::GetSystem()
	{
		if (m_systems.count(typeid(T)) == 0)
			m_systems[typeid(T)] = new ECSystem<T*>(m_capacity);
		auto system = static_cast<ECSystem<T>*>(m_systems[typeid(T)]);
		return system;
	}
}

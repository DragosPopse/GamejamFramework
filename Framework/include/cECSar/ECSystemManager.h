#pragma once
#include <cstdint>
#include "SparseValueSet.h"
#include "Entity.h"
#include <unordered_map>
#include "ECSystem.h"
#include "IComponentSystem.h"
#include "IModule.h"
#include "IEntityFactory.h"
#include "IEntityPack.h"

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

		bool ContainsEntity(int32_t index, int32_t uniqueId= -1) const;
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

		// Modules.
		template <typename T>
		T& GetModule();

		// Factories.
		template <typename T>
		int32_t* CreateFactoryEntities(int32_t count);

		// Packs.
		template <typename T>
		void AddPackToEntity(int32_t index);
		template <typename T>
		void RemovePackFromEntity(int32_t index);

	private:
		int32_t m_globalEntityIdIndex = 0;
		const int32_t m_capacity;

		// Core.
		Utilities::SparseValueSet<Entity>* m_entities;
		std::unordered_map<std::type_index, IECSystem*> m_systems;
		std::unordered_map<std::type_index, IComponentSystem*> m_componentSystems;

		// Utilities.
		std::unordered_map<std::type_index, IModule*> m_modules;
		std::unordered_map<std::type_index, IEntityFactory*> m_factories;
		std::unordered_map<std::type_index, IEntityPack*> m_packs;

		template <typename T>
		ECSystem<T*>& GetSystem();

		template <typename T>
		T& GetPack();
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
			m_componentSystems[typeid(T)] = new T(*this);
		m_componentSystems[typeid(T)]->Update(*this);
	}

	template <typename T>
	T& ECSystemManager::GetModule()
	{
		if (m_modules.count(typeid(T)) == 0)
			m_modules[typeid(T)] = new T(*this);
		return *m_modules[typeid(T)];
	}

	template <typename T>
	int32_t* ECSystemManager::CreateFactoryEntities(const int32_t count)
	{
		if (m_factories.count(typeid(T)) == 0)
			m_factories[typeid(T)] = new T(*this);
		T& factory = m_factories[typeid(T)];

		int32_t* indexes = new int32_t[count];

		for (int32_t i = 0; i < count; ++i)
		{
			const int32_t index = CreateEntity();
			indexes[i] = index;

			factory.OnConstruction(*this, index);
		}

		return indexes;
	}

	template <typename T>
	void ECSystemManager::AddPackToEntity(const int32_t index)
	{
		GetPack<T>().AddToEntity(*this, index);
	}

	template <typename T>
	void ECSystemManager::RemovePackFromEntity(const int32_t index)
	{
		GetPack<T>().RemoveFromEntity(*this, index);
	}

	template <typename T>
	ECSystem<T*>& ECSystemManager::GetSystem()
	{
		if (m_systems.count(typeid(T)) == 0)
			m_systems[typeid(T)] = new ECSystem<T*>(m_capacity);
		auto system = static_cast<ECSystem<T>*>(m_systems[typeid(T)]);
		return system;
	}

	template <typename T>
	T& ECSystemManager::GetPack()
	{
		if (m_packs.count(typeid(T)) == 0)
			m_packs[typeid(T)] = new T(*this);
		return m_packs[typeid(T)];
	}
}

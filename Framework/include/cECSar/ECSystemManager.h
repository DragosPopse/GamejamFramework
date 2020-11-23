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
#include "ECSMapSystem.h"

namespace jam::cecsar
{
	class IECSubscribeable;

	/*
	You don't need to set up anything else besides this class to start working with cecsar.
	Anything you access is automatically instantiated, so you just need to define those classes.

	There are four interfaces you can inherit from, which work with this class.
	- IComponentSystem.
	Inherit to create a system that defines the behaviour for one or more components.
	- IECSubscribable.
	Inherit to be able to subscribe to component related events.
	- IEntityFactory.
	Inherit to be able to create a blueprint for an entity.
	- IModule.
	Inherit to make utility classes that can be accessed from anywhere within the framework.
	An example would be a TextureLibraryModule, or a RenderModule, or TimeModule.
	*/
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
		T& AddSparseComponent(int32_t index);
		template <typename T>
		void RemoveSparseComponent(int32_t index);

		template <typename T>
		T& AddMapComponent(int32_t index);
		template <typename T>
		void RemoveMapComponent(int32_t index);

		template <typename T>
		void Subscribe(IECSubscribeable& subscribeable);
		template <typename T>
		void Unsubscribe(IECSubscribeable& subscribeable);

		template <typename T>
		Utilities::SparseValueSet<T>& GetSparseSet();

		template <typename T>
		std::unordered_map<int32_t, T>& GetMapSet();

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

		int32_t GetCapacity() const;

	private:
		int32_t m_globalEntityIdIndex = 0;
		const int32_t m_capacity;

		// Core.
		Utilities::SparseValueSet<Entity>* m_entities;
		std::unordered_map<std::type_index, IECSystem*> m_sparseSystems;
		std::unordered_map<std::type_index, IECSystem*> m_mapSystems;
		std::unordered_map<std::type_index, IComponentSystem*> m_componentSystems;

		// Utilities.
		std::unordered_map<std::type_index, IModule*> m_modules;
		std::unordered_map<std::type_index, IEntityFactory*> m_factories;
		std::unordered_map<std::type_index, IEntityPack*> m_packs;

		template <typename T>
		ECSystem<T>& GetSparseSystem();

		template <typename T>
		ECSMapSystem<T>& GetMapSystem();

		template <typename T>
		T& GetPack();
	};

	template <typename T>
	T& ECSystemManager::AddSparseComponent(const int32_t index)
	{
		m_entities->instances[index].sparseComponents.insert(typeid(T));

		auto& system = GetSparseSystem<T>();
		system.Add(index);
		return system.set->instances[index];
	}

	template <typename T>
	void ECSystemManager::RemoveSparseComponent(const int32_t index)
	{
		m_entities->instances[index].sparseComponents.erase(typeid(T));

		GetSparseSystem<T>().Remove(index);
	}

	template <typename T>
	T& ECSystemManager::AddMapComponent(const int32_t index)
	{
		m_entities->instances[index].mapComponents.insert(typeid(T));

		auto& system = GetMapSystem<T>();
		system.Add(index);
		return system.map[index];
	}

	template <typename T>
	void ECSystemManager::RemoveMapComponent(const int32_t index)
	{
		m_entities->instances[index].mapComponents.erase(typeid(T));

		GetMapSystem<T>().Remove(index);
	}

	template <typename T>
	void ECSystemManager::Subscribe(IECSubscribeable& subscribeable)
	{
		GetSparseSystem<T>().Subscribe(subscribeable);
	}

	template <typename T>
	void ECSystemManager::Unsubscribe(IECSubscribeable& subscribeable)
	{
		GetSparseSystem<T>().Unsubscribe(subscribeable);
	}

	template <typename T>
	Utilities::SparseValueSet<T>& ECSystemManager::GetSparseSet()
	{
		return *GetSparseSystem<T>().set;
	}

	template <typename T>
	std::unordered_map<int32_t, T>& ECSystemManager::GetMapSet()
	{
		return GetMapSystem<T>().map;
	}

	template <typename T>
	void ECSystemManager::Update()
	{
		if (m_componentSystems.count(typeid(T)) == 0) 
		{
			auto cSystem = new T();
			cSystem->Initialize(*this);
			m_componentSystems[typeid(T)] = cSystem;
		}
		m_componentSystems[typeid(T)]->Update(*this);
	}

	template <typename T>
	T& ECSystemManager::GetModule()
	{
		if (m_modules.count(typeid(T)) == 0) 
		{
			auto module = new T();
			module->Initialize(*this);
			m_modules[typeid(T)] = module;
		}
		return *static_cast<T*>(m_modules[typeid(T)]);
	}

	template <typename T>
	int32_t* ECSystemManager::CreateFactoryEntities(const int32_t count)
	{
		if (m_factories.count(typeid(T)) == 0) 
		{
			auto factory = new T();
			factory->Initialize(*this);
			m_factories[typeid(T)] = factory;
		}

		IEntityFactory& factory = *m_factories[typeid(T)];
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
	ECSystem<T>& ECSystemManager::GetSparseSystem()
	{
		if (m_sparseSystems.count(typeid(T)) == 0) 
			m_sparseSystems[typeid(T)] = new ECSystem<T>(*this, m_capacity);

		ECSystem<T>* system = static_cast<ECSystem<T>*>(m_sparseSystems[typeid(T)]);
		return *system;
	}

	template <typename T>
	ECSMapSystem<T>& ECSystemManager::GetMapSystem()
	{
		if (m_mapSystems.count(typeid(T)) == 0)
			m_mapSystems[typeid(T)] = new ECSMapSystem<T>(*this);

		ECSMapSystem<T>* system = static_cast<ECSMapSystem<T>*>(m_mapSystems[typeid(T)]);
		return *system;
	}

	template <typename T>
	T& ECSystemManager::GetPack()
	{
		if (m_packs.count(typeid(T)) == 0) 
		{
			auto pack = new T();
			pack->Initialize(*this);
			m_packs[typeid(T)] = pack;
		}

		return *static_cast<T*>(m_packs[typeid(T)]);
	}
}

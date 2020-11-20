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
#include "ECSystemSmall.h"

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
		T& AddComponent(int32_t index);
		template <typename T>
		void RemoveComponent(int32_t index);

		template <typename T>
		T& AddComponentSmall(int32_t index);
		template <typename T>
		void RemoveComponentSmall(int32_t index);

		template <typename T>
		void Subscribe(IECSubscribeable& subscribeable);
		template <typename T>
		void Unsubscribe(IECSubscribeable& subscribeable);

		template <typename T>
		Utilities::SparseValueSet<T>& GetSet();

		template <typename T>
		std::unordered_map<int32_t, T>& GetSetSmall();

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
		std::unordered_map<std::type_index, IECSystem*> m_systems;
		std::unordered_map<std::type_index, IECSystem*> m_systemsSmall;
		std::unordered_map<std::type_index, IComponentSystem*> m_componentSystems;

		// Utilities.
		std::unordered_map<std::type_index, IModule*> m_modules;
		std::unordered_map<std::type_index, IEntityFactory*> m_factories;
		std::unordered_map<std::type_index, IEntityPack*> m_packs;

		template <typename T>
		ECSystem<T>& GetSystem();

		template <typename T>
		ECSystemSmall<T>& GetSystemSmall();

		template <typename T>
		T& GetPack();
	};

	template <typename T>
	T& ECSystemManager::AddComponent(const int32_t index)
	{
		m_entities->instances[index].components.insert(typeid(T));

		auto& system = GetSystem<T>();
		system.Add(index);
		return system.set->instances[index];
	}

	template <typename T>
	void ECSystemManager::RemoveComponent(const int32_t index)
	{
		m_entities->instances[index].components.erase(typeid(T));

		GetSystem<T>().Remove(index);
	}

	template <typename T>
	T& ECSystemManager::AddComponentSmall(const int32_t index)
	{
		m_entities->instances[index].componentsSmall.insert(typeid(T));

		auto& system = GetSystemSmall<T>();
		system.Add(index);
		return system.map[index];
	}

	template <typename T>
	void ECSystemManager::RemoveComponentSmall(const int32_t index)
	{
		m_entities->instances[index].componentsSmall.erase(typeid(T));

		GetSystemSmall<T>().Remove(index);
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
		return *GetSystem<T>().set;
	}

	template <typename T>
	std::unordered_map<int32_t, T>& ECSystemManager::GetSetSmall()
	{
		return GetSystemSmall<T>().map;
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
	ECSystem<T>& ECSystemManager::GetSystem()
	{
		if (m_systems.count(typeid(T)) == 0) 
			m_systems[typeid(T)] = new ECSystem<T>(*this, m_capacity);

		ECSystem<T>* system = static_cast<ECSystem<T>*>(m_systems[typeid(T)]);
		return *system;
	}

	template <typename T>
	ECSystemSmall<T>& ECSystemManager::GetSystemSmall()
	{
		if (m_systemsSmall.count(typeid(T)) == 0)
			m_systemsSmall[typeid(T)] = new ECSystemSmall<T>(*this);

		ECSystemSmall<T>* system = static_cast<ECSystemSmall<T>*>(m_systemsSmall[typeid(T)]);
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

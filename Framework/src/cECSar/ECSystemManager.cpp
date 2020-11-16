﻿#include "cECSar/ECSystemManager.h"

jam::cecsar::ECSystemManager::ECSystemManager(const int32_t capacity) :
	m_capacity(capacity),
	m_entities(new Utilities::SparseValueSet<Entity>(capacity))
{
}

jam::cecsar::ECSystemManager::~ECSystemManager()
{
	delete m_entities;
	for (auto system : m_systems)
		delete system.second;
	for (auto system : m_componentSystems)
		delete system.second;
	for (auto system : m_modules)
		delete system.second;
}

int32_t jam::cecsar::ECSystemManager::CreateEntity()
{
	const int32_t index = m_entities->Add();
	m_entities->m_instances[index].m_uniqueId = m_globalEntityIdIndex++;
	return index;
}

void jam::cecsar::ECSystemManager::DestroyEntity(const int32_t index)
{
	auto& entity = m_entities->m_instances[index];
	for (auto component : entity.m_components)
		m_systems[component]->Remove(index);

	m_entities->Remove(index);
}

void jam::cecsar::ECSystemManager::ClearEntities()
{
	for (int32_t i = m_entities->GetCount() - 1; i >= 0; --i)
		DestroyEntity(i);
}

bool jam::cecsar::ECSystemManager::ContainsEntity(const int32_t index, const int32_t uniqueId) const
{
	if (!m_entities->Contains(index))
		return false;
	return uniqueId ? true : m_entities->m_instances[index].m_uniqueId == uniqueId;
}

int32_t jam::cecsar::ECSystemManager::GetEntityUniqueId(const int32_t index) const
{
	return m_entities->operator[](index)->m_uniqueId;
}

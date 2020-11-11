#include "Gamejam/JECS/Core/SystemManager.h"

jam::jecs::SystemManager::~SystemManager()
{
	const int32_t count = _entities.GetCount();
	for (int32_t i = 0; i < count; ++i)
		DestroyEntity(i);

	for (auto systemKeypair : _systems)
		delete systemKeypair.second;
}

int32_t jam::jecs::SystemManager::CreateEntity()
{
	return _entities.Add();
}

void jam::jecs::SystemManager::DestroyEntity(const int32_t index)
{
	const Entity& entity = _entities.instances[index];
	for (auto component : entity)
		_systems[typeid(component)]->OnRemoveComponent(index);
	_entities.Remove(index);
}

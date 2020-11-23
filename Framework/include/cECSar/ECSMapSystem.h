#pragma once
#include <cstdint>
#include "IECSystem.h"
#include <unordered_map>

namespace jam::cecsar
{
	class ECSystemManager;

	template <typename T>
	class ECSMapSystem final : public IECSystem
	{
	public:
		std::unordered_map<int32_t, T> map;

		ECSMapSystem(ECSystemManager& manager);

		void Add(int32_t index) override;
		void Remove(int32_t index) override;
	};

	template <typename T>
	ECSMapSystem<T>::ECSMapSystem(ECSystemManager& manager) :
		IECSystem(manager)
	{

	}

	template <typename T>
	void ECSMapSystem<T>::Add(const int32_t index)
	{
		map[index] = T();
		IECSystem::Add(index);
	}

	template <typename T>
	void ECSMapSystem<T>::Remove(const int32_t index)
	{
		IECSystem::Remove(index);
		map.erase(index);
	}
}

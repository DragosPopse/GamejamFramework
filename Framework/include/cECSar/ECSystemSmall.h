#pragma once
#include <cstdint>
#include "IECSystem.h"
#include <unordered_map>

namespace jam::cecsar
{
	class ECSystemManager;

	template <typename T>
	class ECSystemSmall final : public IECSystem
	{
	public:
		std::unordered_map<int32_t, T> map;

		ECSystemSmall(ECSystemManager& manager);

		void Add(int32_t index) override;
		void Remove(int32_t index) override;
	};

	template <typename T>
	ECSystemSmall<T>::ECSystemSmall(ECSystemManager& manager) :
		IECSystem(manager)
	{

	}

	template <typename T>
	void ECSystemSmall<T>::Add(const int32_t index)
	{
		map[index] = T();
		IECSystem::Add(index);
	}

	template <typename T>
	void ECSystemSmall<T>::Remove(const int32_t index)
	{
		IECSystem::Remove(index);
		map.erase(index);
	}
}

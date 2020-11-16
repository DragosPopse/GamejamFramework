#pragma once
#include "SparseValueSet.h"
#include "IECSubscribeable.h"
#include "IECSystem.h"

namespace jam::cecsar
{
	template <typename T>
	class ECSystem final : IECSystem
	{
	public:
		Utilities::SparseValueSet<T>* m_set;

		ECSystem(int32_t capacity);
		~ECSystem();

		void Add(int32_t index) override;
		void Remove(int32_t index) override;
	};

	template <typename T>
	ECSystem<T>::ECSystem(const int32_t capacity) :
		m_set(new Utilities::SparseValueSet<T>(capacity))
	{
		
	}

	template <typename T>
	ECSystem<T>::~ECSystem()
	{
		delete m_set;
	}

	template <typename T>
	void ECSystem<T>::Add(const int32_t index)
	{
		m_set->Add(index);
		IECSystem::Add(index);
	}

	template <typename T>
	void ECSystem<T>::Remove(const int32_t index)
	{
		IECSystem::Remove(index);
		m_set->Remove(index);
	}
}

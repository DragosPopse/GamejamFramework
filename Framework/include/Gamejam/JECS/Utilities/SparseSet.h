#pragma once
#include <Gamejam/Core/Config.hpp>
#include <cstdint>

namespace Utilities
{
	template <typename T>
	class SparseSet final
	{
	public:
		int32_t* dense;
		int32_t* sparse;
		T* instances;

		T* operator [](int32_t index);

		SparseSet(int32_t capacity);
		~SparseSet();

		int32_t Add();
		void Add(int32_t index);
		void Remove(int32_t index);
		bool Contains(int32_t index) const;
		T* TryGet(int32_t index);

		int32_t GetCount() const;

	private:
		int32_t _count = 0;
		int32_t _capacity;
	};

	template <typename T>
	T* SparseSet<T>::operator[](const int32_t index)
	{
		return &instances[dense[index]];
	}

	template <typename T>
	SparseSet<T>::SparseSet(const int32_t capacity) :
		dense(new int32_t[capacity]()),
		sparse(new int32_t[capacity]()),
		instances(new T[capacity]()),
		_capacity(capacity)
	{

	}

	template <typename T>
	SparseSet<T>::~SparseSet()
	{
		delete[] dense;
		delete[] sparse;
		delete[] instances;
	}

	template <typename T>
	int32_t SparseSet<T>::Add()
	{
		for (int32_t i = 0; i < _capacity; ++i)
		{
			if (Contains(i))
				continue;
			Add(i);
			return i;
		}

		return -1;
	}

	template <typename T>
	void SparseSet<T>::Add(const int32_t index)
	{
		dense[_count] = index;
		sparse[index] = _count++;

		instances[index] = T();
	}

	template <typename T>
	void SparseSet<T>::Remove(const int32_t index)
	{
		const int32_t denseIndex = sparse[index];

		dense[denseIndex] = dense[--_count];
		sparse[dense[denseIndex]] = denseIndex;
	}

	template <typename T>
	bool SparseSet<T>::Contains(const int32_t index) const
	{
		const int32_t denseIndex = sparse[index];
		if (denseIndex >= _count)
			return false;
		return index == dense[denseIndex];
	}

	template <typename T>
	T* SparseSet<T>::TryGet(const int32_t index)
	{
		if (!Contains(index))
			return nullptr;
		return &instances[index];
	}

	template <typename T>
	int32_t SparseSet<T>::GetCount() const
	{
		return _count;
	}
}

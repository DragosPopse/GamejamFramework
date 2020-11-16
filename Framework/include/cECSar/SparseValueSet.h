#pragma once
#include <cstdint>

namespace Utilities
{
	template <typename T>
	class SparseValueSet final
	{
	public:
		int32_t* m_dense;
		T* m_instances;

		T* operator [](int32_t index);

		SparseValueSet(int32_t capacity);
		~SparseValueSet();

		int32_t Add();
		void Add(int32_t index);
		void Remove(int32_t index);
		bool Contains(int32_t index) const;
		T* TryGet(int32_t index);

		int32_t GetCount() const;

	private:
		int32_t* m_sparse;

		int32_t m_count = 0;
		int32_t m_capacity;
	};

	template <typename T>
	T* SparseValueSet<T>::operator[](const int32_t index)
	{
		return &m_instances[m_dense[index]];
	}

	template <typename T>
	SparseValueSet<T>::SparseValueSet(const int32_t capacity) :
		m_dense(new int32_t[capacity]()),
		m_sparse(new int32_t[capacity]()),
		m_instances(new T[capacity]()),
		m_capacity(capacity)
	{

	}

	template <typename T>
	SparseValueSet<T>::~SparseValueSet()
	{
		delete[] m_dense;
		delete[] m_sparse;
		delete[] m_instances;
	}

	template <typename T>
	int32_t SparseValueSet<T>::Add()
	{
		for (int32_t i = 0; i < m_capacity; ++i)
		{
			if (Contains(i))
				continue;
			Add(i);
			return i;
		}

		return -1;
	}

	template <typename T>
	void SparseValueSet<T>::Add(const int32_t index)
	{
		m_dense[m_count] = index;
		m_sparse[index] = m_count++;

		m_instances[index] = T();
	}

	template <typename T>
	void SparseValueSet<T>::Remove(const int32_t index)
	{
		const int32_t denseIndex = m_sparse[index];

		m_dense[denseIndex] = m_dense[--m_count];
		m_sparse[m_dense[denseIndex]] = denseIndex;
	}

	template <typename T>
	bool SparseValueSet<T>::Contains(const int32_t index) const
	{
		const int32_t m_denseIndex = m_sparse[index];
		if (m_denseIndex >= m_count)
			return false;
		return index == m_dense[m_denseIndex];
	}

	template <typename T>
	T* SparseValueSet<T>::TryGet(const int32_t index)
	{
		if (!Contains(index))
			return nullptr;
		return &m_instances[index];
	}

	template <typename T>
	int32_t SparseValueSet<T>::GetCount() const
	{
		return m_count;
	}
}

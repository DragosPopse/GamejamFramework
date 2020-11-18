#pragma once
#include <cstdint>

namespace Utilities
{
	/*
	This is a sort of combination of a map and a normal vector.
	You can access the instances with a key, where the key is an integer.
	You can also use the dense array plus the count to iterate over the populated section of the set.
	*/
	template <typename T>
	class SparseValueSet final
	{
	public:
		int32_t* dense;
		T* instances;

		SparseValueSet(int32_t capacity);
		~SparseValueSet();

		int32_t Add();
		void Add(int32_t index);
		void Remove(int32_t index);
		bool Contains(int32_t index) const;

		int32_t GetCount() const;

	private:
		int32_t* m_sparse;

		int32_t m_count = 0;
		int32_t m_capacity;
	};

	template <typename T>
	SparseValueSet<T>::SparseValueSet(const int32_t capacity) :
		dense(new int32_t[capacity]()),
		m_sparse(new int32_t[capacity]()),
		instances(new T[capacity]()),
		m_capacity(capacity)
	{

	}

	template <typename T>
	SparseValueSet<T>::~SparseValueSet()
	{
		delete[] dense;
		delete[] m_sparse;
		delete[] instances;
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
		if (Contains(index))
			return;

		dense[m_count] = index;
		m_sparse[index] = m_count++;

		instances[index] = T();
	}

	template <typename T>
	void SparseValueSet<T>::Remove(const int32_t index)
	{
		if (!Contains(index))
			return;

		const int32_t denseIndex = m_sparse[index];

		dense[denseIndex] = dense[--m_count];
		m_sparse[dense[denseIndex]] = denseIndex;
	}

	template <typename T>
	bool SparseValueSet<T>::Contains(const int32_t index) const
	{
		const int32_t m_denseIndex = m_sparse[index];
		if (m_denseIndex >= m_count)
			return false;
		return index == dense[m_denseIndex];
	}

	template <typename T>
	int32_t SparseValueSet<T>::GetCount() const
	{
		return m_count;
	}
}

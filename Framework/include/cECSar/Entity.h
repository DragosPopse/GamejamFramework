#pragma once
#include <typeindex>
#include <unordered_set>

namespace jam::cecsar
{
	class Entity final
	{
	public:
		int32_t m_uniqueId = -1;
		std::unordered_set<std::type_index> m_components;
	};
}

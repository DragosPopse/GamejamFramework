#pragma once
#include <typeindex>
#include <unordered_set>

namespace jam::cecsar
{
	class Entity final
	{
	public:
		int32_t uniqueId = -1;
		std::unordered_set<std::type_index> sparseComponents;
		std::unordered_set<std::type_index> mapComponents;
	};
}

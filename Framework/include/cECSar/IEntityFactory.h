#pragma once
#include <cstdint>

namespace jam::cecsar
{
	class ECSystemManager;

	class IEntityFactory
	{
	public:
		IEntityFactory(ECSystemManager& manager);
		virtual ~IEntityFactory();

		virtual void OnConstruction(ECSystemManager& manager, int32_t index) = 0;
	};
}
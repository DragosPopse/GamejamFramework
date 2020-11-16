#pragma once
#include <cstdint>

namespace jam::cecsar
{
	class ECSystemManager;

	class IEntityPack
	{
	public:
		IEntityPack(ECSystemManager& manager);
		virtual ~IEntityPack();

		virtual void AddToEntity(ECSystemManager& manager, int32_t index) = 0;
		virtual void RemoveFromEntity(ECSystemManager& manager, int32_t index) = 0;
	};
}

#pragma once
#include <cstdint>

namespace jam::cecsar
{
	class ECSystemManager;

	class IEntityPack
	{
		friend ECSystemManager;

	public:
		virtual ~IEntityPack();

		virtual void AddToEntity(ECSystemManager& manager, int32_t index) = 0;
		virtual void RemoveFromEntity(ECSystemManager& manager, int32_t index) = 0;

	protected:
		virtual void Initialize(ECSystemManager& manager);
	};
}

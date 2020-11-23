#pragma once
#include <cstdint>

namespace jam::cecsar
{
	class ECSystemManager;

	/*
	You can inherit this interface to make it automatically generated
	and accessable for everything within the ECSystemManager.

	You can define a blueprint for an entity here.
	You can add components to the target entity, call events, set variables and so on.
	*/
	class IEntityFactory
	{
		friend ECSystemManager;

	public:
		virtual ~IEntityFactory();
		virtual void OnConstruction(ECSystemManager& manager, int32_t index) = 0;

	protected:
		virtual void Initialize(ECSystemManager& manager);
	};
}
#pragma once
#include "Gamejam/JECS/Core/EntityFactory.h"

namespace jam
{
	class SandFactory final : public jecs::EntityFactory
	{
	public:
		SandFactory(jecs::SystemManager& manager);

	protected:
		void OnConstruction() override;
	};
}
#pragma once
#include <Gamejam/Core/Config.hpp>
#include "Gamejam/JECS/Core/EntityFactory.h"

namespace jam::demo
{
	class DemoDummyFactory final : public jecs::EntityFactory
	{
	public:
		DemoDummyFactory(jecs::SystemManager& manager);

	protected:
		void OnConstruction() override;
	};
}

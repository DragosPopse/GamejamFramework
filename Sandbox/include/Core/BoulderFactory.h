#pragma once
#include "Gamejam/JECS/Core/EntityFactory.h"

namespace jam
{
	class BoulderFactory final : public jecs::EntityFactory
	{
	public:
		BoulderFactory(jecs::SystemManager& manager);

	protected:
		void OnConstruction() override;
	};
}
#pragma once
#include "Gamejam/JECS/Core/EntityFactory.h"

namespace jam
{
	class AntFactory final : public jecs::EntityFactory
	{
	public:
		AntFactory(jecs::SystemManager& manager);

	protected:
		void OnConstruction() override;
	};
}

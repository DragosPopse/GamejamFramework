#pragma once
#include "Gamejam/JECS/Core/EntityFactory.h"

namespace demo
{
	class AntFactory final : public jam::jecs::EntityFactory
	{
	protected:
		void OnConstruction() override;
	};
}

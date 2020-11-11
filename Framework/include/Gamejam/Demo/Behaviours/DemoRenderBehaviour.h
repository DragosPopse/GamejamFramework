#pragma once
#include <Gamejam/Core/Config.hpp>
#include "Gamejam/JECS/Core/ISystemBehaviour.h"
#include "Gamejam/JECS/Core/SystemManager.h"
#include "Gamejam/Demo/Components/DemoRenderComponent.h"

namespace jam::demo
{
	class DemoRenderBehaviour final : public jecs::ISystemBehaviour<DemoRenderComponent>
	{
	public:
		float m_zoom = 1;
		double m_angle = 0;
		float xOffset = 0, yOffset = 0;
		
		DemoRenderBehaviour(jecs::SystemManager& manager);
		~DemoRenderBehaviour();
		void Update();

	private:
		SDL_Texture* m_texture;

		void PreRender() const;
		void PostRender() const;
	};
}

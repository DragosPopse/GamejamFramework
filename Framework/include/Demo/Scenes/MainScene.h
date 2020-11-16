#pragma once
#include "Gamejam/SceneManagement/Scene.hpp"
#include "cECSar/ECSystemManager.h"

namespace jam::demo
{
	class MainScene final : public Scene
	{
	public:
		bool Update(float dt) override;
		bool FixedUpdate(float dt) override;
		bool Render() override;
		void Enable() override;
		void Disable() override;

	private:
		cecsar::ECSystemManager m_ecsManager = cecsar::ECSystemManager(1000);
	};
}

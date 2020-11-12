#include <Precomp/Precomp.h>
#include "Managers/TileMapper.h"
#include "Gamejam/JECS/Core/SystemManager.h"
#include "Gamejam/Demo/Behaviours/DemoRenderBehaviour.h"
#include "Gamejam/Demo/Behaviours/DemoCollisionBehaviour.h"
#include "AntBehaviour.h"
#include "SmoothMovementBehaviour.h"

namespace jam
{
	class MainScene final : public Scene
	{
	public:
		MainScene();
		~MainScene();

		void Enable() override;
		void Disable() override;

		bool Update(float deltaTime) override;
		bool Render() override;

	private:
		jecs::SystemManager* m_systemManager = nullptr;
		demo::DemoRenderBehaviour* m_renderBehaviour = nullptr;
		demo::DemoCollisionBehaviour* m_collisionBehaviour = nullptr;

		AntBehaviour* m_antBehaviour = nullptr;
		SmoothMovementBehaviour* m_smoothMovementBehaviour = nullptr;
	};
}

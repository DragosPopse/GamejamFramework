#include <Precomp/Precomp.h>
#include "Managers/TileManager.h"
#include "Gamejam/JECS/Core/SystemManager.h"
#include "Gamejam/Demo/Behaviours/DemoRenderBehaviour.h"
#include "Gamejam/Demo/Behaviours/DemoCollisionBehaviour.h"
#include "AntBehaviour.h"
#include "SmoothMovementBehaviour.h"
#include "AnimatorBehaviour.h"
#include "SandBehaviour.h"
#include "Core/GravityBehaviour.h"

namespace jam
{
	class MainScene final : public Scene
	{
	public:
		MainScene();
		~MainScene();

		void Enable() override;
		void Disable() override;
		void CreateEntities();

		bool Update(float deltaTime) override;
		bool Render() override;

	private:
		jecs::SystemManager* m_systemManager = nullptr;
		demo::DemoRenderBehaviour* m_renderBehaviour = nullptr;
		demo::DemoCollisionBehaviour* m_collisionBehaviour = nullptr;

		AntBehaviour* m_antBehaviour = nullptr;
		SmoothMovementBehaviour* m_smoothMovementBehaviour = nullptr;
		SandBehaviour* m_sandBehaviour = nullptr;
		GravityBehaviour* m_gravityBehaviour = nullptr;

		AnimatorBehaviour* m_animatorBehaviour = nullptr;
	};
}

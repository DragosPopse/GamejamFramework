#include <Precomp/Precomp.h>
#include "cECSar/ECSystemManager.h"

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
		cecsar::ECSystemManager m_manager = cecsar::ECSystemManager(1000);
	};
}

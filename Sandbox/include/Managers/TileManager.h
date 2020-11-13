#include "Precomp/Precomp.h"

using std::vector;
using std::string;

namespace jam
{
	class TileManager
	{
	public:
		static TileManager* GetInstance();
		bool HasTile(float x, float y, int& index);

		SDL_Texture* GetMap();

		SDL_Texture* m_Background;


	private:
		TileManager();
		void LoadMap();
		void GenerateMap(string path);
		static TileManager* m_Instance;
		vector<vector<int>> m_Grid;
		string m_MapDefaultPath = "files/tileSheet.png";
	};
}
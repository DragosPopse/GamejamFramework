#include "Precomp/Precomp.h"

using std::vector;
using std::string;

namespace jam
{
	class TileMapper
	{
	public:
		static TileMapper* GetInstance();
		bool HasTile(float x, float y, int& index);

	private:
		TileMapper();
		void LoadMap();
		static TileMapper* m_Instance;
		vector<vector<int>> m_Grid;
	};
}
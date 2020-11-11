#include "Precomp/Precomp.h"
#include "Managers/TileMapper.h"
#include <fstream>
#include <string>
#include <sstream>

namespace jam
{
	TileMapper* TileMapper::m_Instance = nullptr;

	TileMapper::TileMapper()
	{
		LoadMap();
	}

	// https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
	void TileMapper::LoadMap()
	{
		std::ifstream file("files/Grid.csv");

		if (!file.is_open())
		{
			throw "Could not open file";
			exit(1);
		}
		
		string line;
		int val;
		bool firstLine = true;

		int rowIndx = 0;

		while (std::getline(file, line, '#'))
		{
			std::stringstream ss(line);

			while (ss >> val)
			{
				if (rowIndx >= m_Grid.size())
				{
					vector<int> row = vector<int>();
					m_Grid.push_back(row);
				}

				m_Grid[rowIndx].push_back(val);

				if (ss.peek() == ',') ss.ignore();
			}

			rowIndx++;
		}

		file.close();
	}

	TileMapper* TileMapper::GetInstance()
	{
		if (m_Instance == nullptr)
		{
			m_Instance = new TileMapper();
		}

		return m_Instance;
	}

	bool TileMapper::HasTile(float x, float y, int& index)
	{
		return false;
	}
}
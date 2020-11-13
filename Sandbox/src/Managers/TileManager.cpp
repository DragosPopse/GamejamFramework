#include "Precomp/Precomp.h"
#include "Managers/TileManager.h"
#include <fstream>
#include <string>
#include <sstream>

namespace jam
{
	TileManager* TileManager::m_Instance = nullptr;

	TileManager::TileManager()
	{
		LoadMap();
		GenerateMap(m_MapDefaultPath);
	}

	// https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
	void TileManager::LoadMap()
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

	void TileManager::GenerateMap(string path)
	{
		int w, h;
		SDL_GetRendererOutputSize(App::Get().m_renderer, &w, &h);

		Uint32 rMask = 0x00000000;
		Uint32 gMask = 0x00000000;
		Uint32 bMask = 0x00000000;
		Uint32 aMask = 0x00000000;

		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)														//taken from https://wiki.libsdl.org/SDL_CreateRGBSurface because I was lazy
		{
			rMask = 0xff000000;
			gMask = 0x00ff0000;
			bMask = 0x0000ff00;
			aMask = 0x000000ff;
		}
		else {
			rMask = 0x000000ff;
			gMask = 0x0000ff00;
			bMask = 0x00ff0000;
			aMask = 0xff000000;
		}

		SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, w, h, 32, rMask, gMask, bMask, aMask);	//create empty rgb Surface tempSurface depending on RendererSize & byte order of the users machine
		

		const char* c = path.c_str();
		SDL_Surface* tileSheet = IMG_Load(c);														//loading tileSheet into Surface

		for (int r = 0; r < m_Grid.size(); r++)														//copies tiles from tileSheet to tempSurface (scales them from 256x256 to 32x32, to change the scaling, 
		{																							//change scaleTox/scaleToY to the corresponding sizes
			for (int c = 0; c < m_Grid[r].size(); c++)
			{
				int tileIndex = m_Grid[r][c];

				SDL_Rect srcRect;						
				srcRect.x = tileIndex * 256;
				srcRect.y = 0;
				srcRect.w = 256;
				srcRect.h = 256;

				int scaleToX = 32;
				int scaleToY = 32;

				SDL_Rect dstRect;
				dstRect.x = c * scaleToX;
				dstRect.y = r * scaleToY;
				dstRect.w = scaleToX;
				dstRect.h = scaleToY;

				SDL_BlitScaled(tileSheet, &srcRect, tempSurface, &dstRect);
			}
		}

		m_Background = SDL_CreateTextureFromSurface(App::Get().m_renderer, tempSurface);
		SDL_FreeSurface(tempSurface);
		SDL_FreeSurface(tileSheet);
	}

	TileManager* TileManager::GetInstance()
	{
		if (m_Instance == nullptr)
		{
			m_Instance = new TileManager();
		}

		return m_Instance;
	}

	bool TileManager::HasTile(float x, float y, int& index)
	{
		return false;
	}
	SDL_Texture* TileManager::GetMap()
	{
		return m_Background;
	}
}
#pragma once
#include "cECSar/IModule.h"
#include "SDL.h"
#include <string>
#include <unordered_map>

namespace jam::demo
{
	class RenderModule final : public cecsar::IModule
	{
	public:
		int32_t spriteSize = 8;
		float scale = 1;

		float zoom = 1;
		float degrees = 0;
		float xOffset = 0, yOffset = 0;

		float xCameraOffset = 0, yCameraOffset = 0;

		float depth = 0;
		float minDepth = .2;
		float depthModifier = 1;

		int32_t colorForegroundClear = 0xff;
		int32_t colorBackgroundClear = 0x00;

		RenderModule();
		~RenderModule();

		void PreRender() const;
		void PostRender() const;

		SDL_Texture* GetTexture(const std::string& path);
		void Clear();

	private:
		std::unordered_map<std::string, SDL_Texture*> m_textureMap;
		SDL_Texture* m_texture;
	};
}

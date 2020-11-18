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
		float m_zoom = 1;
		float m_angle = 0;
		float m_xOffset = 0, m_yOffset = 0;
		float m_xCameraOffset = 0, m_yCameraOffset = 0;

		int32_t m_colorForegroundClear = 0xff;
		int32_t m_colorBackgroundClear = 0x00;

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

#include "Demo/Modules/RenderModule.h"

jam::demo::RenderModule::RenderModule(cecsar::ECSystemManager& manager) :
	IModule(manager)
{
}

SDL_Texture* jam::demo::RenderModule::GetTexture(const std::string path)
{
	return nullptr;
}

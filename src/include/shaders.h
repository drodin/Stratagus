#ifndef __SHADERS_H__
#define __SHADERS_H__

#include <SDL.h>

#if !defined(__APPLE__) && !defined(ANDROID)
extern bool LoadShaderExtensions();
extern bool RenderWithShader(SDL_Renderer *renderer, SDL_Window* win, SDL_Texture* backBuffer);
#else
#include "stratagus.h"

inline bool LoadShaderExtensions() {
    return false;
}

inline bool RenderWithShader(SDL_Renderer*, SDL_Window*, SDL_Texture*) {
    return false;
}
#endif

#endif

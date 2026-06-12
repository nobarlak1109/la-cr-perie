#pragma once
#include "../Model/Base.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

class Platform : public Base
{
public:
    bool Init(const char* title, int width, int height);
    void Shutdown();
    void NewFrame();
    void Render();
    bool PollEvents();          // returns false when app should close

    SDL_Window*   GetWindow()  const { return window;  }
    SDL_GLContext GetContext() const { return glContext; }

private:
    SDL_Window*   window    = nullptr;
    SDL_GLContext glContext  = nullptr;
    ImVec4        clearColor = {0.1f, 0.1f, 0.1f, 1.0f};
};

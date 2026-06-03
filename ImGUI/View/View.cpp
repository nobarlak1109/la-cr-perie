#include "View.h"

View::View()
    : factoryController(&factoryModel),
      dashboard(&factoryModel, &factoryController)
{
}

bool View::Init()
{
    return platform.Init("Crêperie", 1280, 800);
}

void View::Run()
{
    bool running = true;
    while(running)
    {
        running = platform.PollEvents();
        platform.NewFrame();

        dashboard.DrawAll();

        platform.Render();
    }
}

void View::Shutdown()
{
    platform.Shutdown();
}

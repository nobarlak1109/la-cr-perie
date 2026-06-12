#pragma once
#include "../Controller/FactoryController.h"
#include "../Model/Base.h"
#include "../Model/FactoryModel.h"
#include "Platform.h"
#include "UI/MainDashboard.h"

class View : public Base
{
public:
    View();
    bool Init();
    void Run();         // ← owns the main loop
    void Shutdown();

private:
    Platform platform;
    FactoryModel factoryModel;
    FactoryController factoryController;
    MainDashboard dashboard;
};

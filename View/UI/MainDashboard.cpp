#include "MainDashboard.h"

#include <iostream>

MainDashboard::MainDashboard(FactoryModel* factoryModel, FactoryController* factoryController)
{
    SetFactoryModel(factoryModel);
    SetFactoryController(factoryController);
}

void MainDashboard::SetFactoryModel(FactoryModel* factoryModel)
{
    this->factoryModel = factoryModel;
    factoryFloorViewer.SetFactoryModel(factoryModel);
    machineStatusViewer.SetFactoryModel(factoryModel);
    inventoryViewer.SetFactoryModel(factoryModel);
}

void MainDashboard::SetFactoryController(FactoryController* factoryController)
{
    this->factoryController = factoryController;
    controlPanelViewer.SetController(factoryController);
}

void MainDashboard::Draw(ImVec2 pos, ImVec2 size)
{
    DrawAll();
}

void MainDashboard::DrawAll()
{
    ImGuiIO& io = ImGui::GetIO();
    float width = io.DisplaySize.x;
    float height = io.DisplaySize.y;

    float leftColW = 300.0f;
    float rightColW = 250.0f;
    float ctrlH = 120.0f;

    controlPanelViewer.Draw({0, 0}, {leftColW, ctrlH});
    ControlActions actions = controlPanelViewer.GetActions();
    if(actions.startPressed) std::cout << "START\n";
    if(actions.stopPressed) std::cout << "STOP\n";
    if(actions.resetPressed) std::cout << "RESET\n";

    std::vector<MachineViewData> machines =
    {
        {"Scale", 5, 42, 0.6f, MachineState::Idle},
        {"Mixer", 3, 10, 0.8f, MachineState::Idle},
        {"Cooker", 2, 8, 0.5f, MachineState::Idle}
    };
    machineStatusViewer.SetMachines(machines);
    machineStatusViewer.Draw({0, ctrlH}, {leftColW, height - ctrlH});

    InventoryViewData inventory;
    inventory.eggs = 0;
    inventory.flour = 0;
    inventory.milk = 0;
    inventory.toppings = 0;
    inventory.uncookedDough = 0;
    inventory.cookedDough = 0;
    inventory.crepes = 0;
    inventory.lost = 0;
    inventoryViewer.SetInventory(inventory);
    inventoryViewer.Draw({width - rightColW, 0}, {rightColW, height});

    factoryFloorViewer.Draw({leftColW, 0}, {width - leftColW - rightColW, height});
}

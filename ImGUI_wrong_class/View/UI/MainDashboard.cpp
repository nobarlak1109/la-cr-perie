#include "MainDashboard.h"

#include <string>

MainDashboard::MainDashboard(
    FactoryModel* factoryModel,
    FactoryController* factoryController)
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

    std::vector<MachineViewData> machines;
    InventoryViewData inventory;

    if (factoryController)
    {
        const auto& modelMachines =
            factoryController->getMachines();

        machines.reserve(modelMachines.size());

        for (const auto& machinePtr : modelMachines)
        {
            if (!machinePtr)
                continue;

            MachineViewData view;

            std::string name = machinePtr->getName();

            view.machineName =
                name.empty()
                    ? std::string("Machine")
                    : std::move(name);

            view.itemsInQueue =
                machinePtr->getQueueCount();

            view.itemsProcessed =
                machinePtr->getItemsProcessed();

            view.progress =
                machinePtr->getProgress();

            if (machinePtr->isBroken())
            {
                view.state = MachineState::Broken;
            }
            else if (machinePtr->isRunning())
            {
                view.state = MachineState::Running;
            }
            else
            {
                view.state = MachineState::Idle;
            }

            machines.push_back(std::move(view));
        }

        const auto& ingredients =
            factoryController->getInventory().getIngredients();

        for (const auto& ingredient : ingredients)
        {
            if (!ingredient)
                continue;

            std::string type = ingredient->getType();

            if (type == "Egg")
                inventory.eggs++;

            else if (type == "Flour")
                inventory.flour++;

            else if (type == "Milk")
                inventory.milk++;

            else if (type == "Topping")
                inventory.toppings++;

            else if (type == "UncookedDough")
                inventory.uncookedDough++;

            else if (type == "CookedDough")
                inventory.cookedDough++;
        }

        const auto& products =
            factoryController->getInventory().getProducts();

        for (const auto& product : products)
        {
            if (!product)
                continue;

            if (product->getProductName() == "Crepe")
            {
                inventory.crepes++;
            }
        }

        // Overflow mode statistics
        inventory.lostItems =
            factoryController->getLostItems();
    }

    machineStatusViewer.SetMachines(machines);

    machineStatusViewer.Draw(
        {0, ctrlH},
        {leftColW, height - ctrlH});

    inventoryViewer.SetInventory(inventory);

    inventoryViewer.Draw(
        {width - rightColW, 0},
        {rightColW, height});

    factoryFloorViewer.Draw(
        {leftColW, 0},
        {width - leftColW - rightColW, height});
}
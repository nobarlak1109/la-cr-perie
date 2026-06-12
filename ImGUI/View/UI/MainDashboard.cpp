#include "MainDashboard.h"

#include <string>

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
    float ctrlH = 170.0f;

    controlPanelViewer.Draw({0, 0}, {leftColW, ctrlH});

    std::vector<MachineViewData> machines;
    InventoryViewData inventory;

    if(factoryController)
    {
        const auto& modelMachines = factoryController->getMachines();
        machines.reserve(modelMachines.size());

        for(const auto& machinePtr : modelMachines)
        {
            if(!machinePtr)
                continue;

            MachineViewData view;
            std::string name = machinePtr->getName();
            view.machineName = name.empty() ? std::string("Machine") : std::move(name);
            view.itemsInQueue = machinePtr->getQueueCount();
            view.itemsProcessed = machinePtr->getItemsProcessed();
            view.progress = machinePtr->getProgress();

            if(machinePtr->isBroken())
                view.state = MachineState::Broken;
            else if(machinePtr->isRunning())
                view.state = MachineState::Running;
            else
                view.state = MachineState::Idle;

            machines.push_back(std::move(view));
        }

        const auto& ingredients = factoryController->getInventory().getIngredients();
        for(const auto& ingredient : ingredients)
        {
            if(!ingredient)
                continue;

            std::string type = ingredient->getType();
            if(type == "Egg")
                inventory.eggs++;
            else if(type == "Flour")
                inventory.flour++;
            else if(type == "Milk")
                inventory.milk++;
            else if(type == "Topping")
                inventory.toppings++;
            else if(type == "UncookedDough")
                inventory.uncookedDough++;
            else if(type == "CookedDough")
                inventory.cookedDough++;
        }

        const auto& products = factoryController->getInventory().getProducts();
        for(const auto& product : products)
        {
            if(product && product->getProductName() == "Crepe")
                inventory.crepes++;
        }

        inventory.lostItems = factoryController->getLostItems();
    }

    machineStatusViewer.SetMachines(machines);
    machineStatusViewer.Draw({0, ctrlH}, {leftColW, height - ctrlH});

    float inspectorH = 190.0f;
    inventoryViewer.SetInventory(inventory);
    inventoryViewer.Draw({width - rightColW, 0}, {rightColW, height - inspectorH});

    float factoryTop = height * 0.14f;
    float factoryHeight = height * 0.52f;
    float factoryLogTop = factoryTop + factoryHeight + 8.0f;
    float factoryLogHeight = height - factoryLogTop;
    float centerW = width - leftColW - rightColW;

    factoryFloorViewer.Draw({leftColW, factoryTop}, {width - leftColW - rightColW, factoryHeight});
    DrawFactoryLog({leftColW, factoryLogTop}, {centerW, factoryLogHeight});

    DrawMachineInspector({width - rightColW, height - inspectorH}, {rightColW, inspectorH});
}

void MainDashboard::DrawMachineInspector(ImVec2 pos, ImVec2 size)
{
    ImGui::SetNextWindowPos(pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(size, ImGuiCond_Always);
    ImGui::Begin("Machine Inspector", nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse);

    int selectedIndex = factoryFloorViewer.GetSelectedMachineIndex();
    Machine* selectedMachine = nullptr;

    if(factoryModel && selectedIndex >= 0)
    {
        const auto& machines = factoryModel->getMachines();
        if(selectedIndex < static_cast<int>(machines.size()) && machines[selectedIndex])
            selectedMachine = machines[selectedIndex].get();
    }

    if(!selectedMachine)
    {
        ImGui::TextWrapped("Click a machine in the factory panel.");
        ImGui::End();
        return;
    }

    std::string name = selectedMachine->getName();
    if(name.empty())
        name = "Machine";

    ImGui::Text("Selected: %s", name.c_str());
    ImGui::Separator();
    ImGui::Text("State: %s", selectedMachine->getStatus().c_str());
    ImGui::Text("Queue: %d / %d", selectedMachine->getQueueCount(), selectedMachine->getMaxQueueSize());
    ImGui::Text("Processed: %d", selectedMachine->getItemsProcessed());
    ImGui::ProgressBar(selectedMachine->getProgress(), ImVec2(-1.0f, 0.0f));

    if(ImGui::Button(selectedMachine->isBroken() ? "Clear Forced Breakdown" : "Force Breakdown"))
    {
        bool broken = !selectedMachine->isBroken();
        selectedMachine->setBroken(broken);

        if(factoryModel)
            factoryModel->addLog(name + (broken ? " broken!" : " fixed!"));
    }

    if(ImGui::Button("Instant Repair"))
    {
        bool wasBroken = selectedMachine->isBroken();
        selectedMachine->repair();

        if(wasBroken && factoryModel)
            factoryModel->addLog(name + " fixed!");
    }

    ImGui::End();
}

void MainDashboard::DrawFactoryLog(ImVec2 pos, ImVec2 size)
{
    ImGui::SetNextWindowPos(pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(size, ImGuiCond_Always);
    ImGui::Begin("Factory Log", nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse);

    if(!factoryModel)
    {
        ImGui::TextWrapped("No factory model connected.");
        ImGui::End();
        return;
    }

    const auto& logs = factoryModel->getLogs();
    if(logs.empty())
    {
        ImGui::TextWrapped("No production events yet.");
        ImGui::End();
        return;
    }

    ImGui::BeginChild("FactoryLogScroll", ImVec2(0, 0), false);
    for(const std::string& log : logs)
        ImGui::TextWrapped("%s", log.c_str());

    if(ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);

    ImGui::EndChild();
    ImGui::End();
}

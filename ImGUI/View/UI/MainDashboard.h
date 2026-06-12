#pragma once

#include "../../Controller/FactoryController.h"
#include "../../Model/FactoryModel.h"
#include "ControlPanelViewer.h"
#include "FactoryFloorViewer.h"
#include "InventoryViewer.h"
#include "MachineStatusViewer.h"

class MainDashboard : public BaseViewer
{
public:
    MainDashboard(FactoryModel* factoryModel = nullptr, FactoryController* factoryController = nullptr);

    FactoryModel* GetFactoryModel() const { return factoryModel; }
    void SetFactoryModel(FactoryModel* factoryModel);

    FactoryController* GetFactoryController() const { return factoryController; }
    void SetFactoryController(FactoryController* factoryController);

    void Draw(ImVec2 pos, ImVec2 size) override;
    void DrawAll();

private:
    void DrawMachineInspector(ImVec2 pos, ImVec2 size);
    void DrawFactoryLog(ImVec2 pos, ImVec2 size);

    FactoryModel* factoryModel = nullptr;
    FactoryController* factoryController = nullptr;

    FactoryFloorViewer factoryFloorViewer;
    ControlPanelViewer controlPanelViewer;
    MachineStatusViewer machineStatusViewer;
    InventoryViewer inventoryViewer;
};

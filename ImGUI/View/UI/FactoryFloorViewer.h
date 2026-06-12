#pragma once

#include "BaseViewer.h"
#include "../../Model/FactoryModel.h"

class FactoryFloorViewer : public BaseViewer
{
public:
    explicit FactoryFloorViewer(FactoryModel* factoryModel = nullptr) : factoryModel(factoryModel) {}

    FactoryModel* GetFactoryModel() const { return factoryModel; }
    void SetFactoryModel(FactoryModel* factoryModel) { this->factoryModel = factoryModel; }

    void Draw(ImVec2 pos, ImVec2 size) override;
    void DrawMachines();
    void DrawConveyors();

    int GetSelectedMachineIndex() const { return selectedMachineIndex; }

private:
    FactoryModel* factoryModel = nullptr;
    int selectedMachineIndex = -1;
};

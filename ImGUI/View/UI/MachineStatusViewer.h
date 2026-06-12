#pragma once

#include "BaseViewer.h"
#include "../../Model/FactoryModel.h"

#include <string>
#include <vector>

enum class MachineState
{
    Idle,
    Running,
    Overloaded,
    Broken
};

struct MachineViewData : public Base
{
    std::string machineName = "Machine";
    int itemsInQueue = 0;
    int itemsProcessed = 0;
    float progress = 0.0f;
    MachineState state = MachineState::Idle;
};

class MachineStatusViewer : public BaseViewer
{
public:
    explicit MachineStatusViewer(FactoryModel* factoryModel = nullptr) : factoryModel(factoryModel) {}

    FactoryModel* GetFactoryModel() const { return factoryModel; }
    void SetFactoryModel(FactoryModel* factoryModel) { this->factoryModel = factoryModel; }

    void SetMachines(const std::vector<MachineViewData>& machines) { this->machines = machines; }
    const std::vector<MachineViewData>& GetMachines() const { return machines; }

    void Draw(ImVec2 pos, ImVec2 size) override;
    void DrawMachineStatus();

private:
    void DrawMachine(const MachineViewData& machine);
    void DrawState(MachineState state);

    FactoryModel* factoryModel = nullptr;
    std::vector<MachineViewData> machines;
};

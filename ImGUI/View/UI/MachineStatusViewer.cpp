#include "MachineStatusViewer.h"

void MachineStatusViewer::Draw(ImVec2 pos, ImVec2 size)
{
    ImGui::SetNextWindowPos(pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(size, ImGuiCond_Always);
    ImGui::Begin("Machine Status", nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse);

    DrawMachineStatus();

    ImGui::End();
}

void MachineStatusViewer::DrawMachineStatus()
{
    for(const MachineViewData& machine : machines)
    {
        DrawMachine(machine);
        ImGui::Separator();
    }
}

void MachineStatusViewer::DrawMachine(const MachineViewData& machine)
{
    ImGui::Text("-- %s --", machine.machineName);
    DrawState(machine.state);
    ImGui::ProgressBar(machine.progress, ImVec2(-1, 0));
    ImGui::Text("Items in Queue:   %d", machine.itemsInQueue);
    ImGui::Text("Items Processed:  %d", machine.itemsProcessed);
}

void MachineStatusViewer::DrawState(MachineState state)
{
    switch(state)
    {
        case MachineState::Idle:
            ImGui::TextColored({0.5f, 0.5f, 0.5f, 1.0f}, "State: Idle");
            break;
        case MachineState::Running:
            ImGui::TextColored({0.0f, 1.0f, 0.0f, 1.0f}, "State: Running");
            break;
        case MachineState::Overloaded:
            ImGui::TextColored({1.0f, 0.5f, 0.0f, 1.0f}, "State: Overloaded");
            break;
        case MachineState::Broken:
            ImGui::TextColored({1.0f, 0.0f, 0.0f, 1.0f}, "State: Broken");
            break;
    }
}


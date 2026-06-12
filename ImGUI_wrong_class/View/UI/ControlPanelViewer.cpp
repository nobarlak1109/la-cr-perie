#include "ControlPanelViewer.h"

void ControlPanelViewer::Draw(ImVec2 pos, ImVec2 size)
{
    lastActions = {};

    // Sync FROM backend (only here, before UI)
    if (controller)
    {
        flowModeIndex = static_cast<int>(controller->getFlowMode());
    }

    ImGui::SetNextWindowPos(pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(size, ImGuiCond_Always);

    ImGui::Begin("Control Panel", nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse);

    ImGui::Text("-- Controls --");
    ImGui::Separator();

    DrawStartStopButtons();
    DrawScenarioButtons();

    // Flow mode dropdown
    const char* modes[] =
{
    "Normal",
    "Bottleneck",
    "Random Breakdown",
    "Overflow"
};

    int localMode = flowModeIndex; // IMPORTANT: local copy for ImGui

    if (ImGui::Combo("Flow Mode", &localMode, modes, IM_ARRAYSIZE(modes)))
    {
        flowModeIndex = localMode; // update UI state

        if (controller)
        {
            controller->setFlowMode(
                static_cast<FactoryModel::FlowMode>(localMode));
        }
    }

    // keep UI state in sync after interaction
    flowModeIndex = localMode;

    if (ImGui::SliderInt("Speed", &speed, 1, 10))
    {
        lastActions.requestedSpeed = speed;
        if (controller)
            controller->setSpeed(speed);
    }
    else
    {
        lastActions.requestedSpeed = speed;
    }

    ImGui::End();
}

void ControlPanelViewer::DrawStartStopButtons()
{
    if (ImGui::Button("Start"))
    {
        lastActions.startPressed = true;
        if (controller) controller->startSimulation();
    }

    ImGui::SameLine();

    if (ImGui::Button("Stop"))
    {
        lastActions.stopPressed = true;
        if (controller) controller->stopSimulation();
    }
}

void ControlPanelViewer::DrawScenarioButtons()
{
    ImGui::SameLine();

    if (ImGui::Button("Reset"))
    {
        lastActions.resetPressed = true;

        speed = 1;

        if (controller) controller->resetSimulation();
        if (controller) controller->setSpeed(speed);
    }
}
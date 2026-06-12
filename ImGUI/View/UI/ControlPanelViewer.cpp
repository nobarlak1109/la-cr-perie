#include "ControlPanelViewer.h"

void ControlPanelViewer::Draw(ImVec2 pos, ImVec2 size)
{
    lastActions = {};

    if(controller)
        flowModeIndex = static_cast<int>(controller->getFlowMode());

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

    const char* modes[] =
    {
        "Normal",
        "Bottleneck",
        "Random Breakdown",
        "Overflow",
        "Short Supply"
    };

    int selectedMode = flowModeIndex;
    if(ImGui::Combo("Flow Mode", &selectedMode, modes, IM_ARRAYSIZE(modes)))
    {
        flowModeIndex = selectedMode;
        if(controller)
            controller->setFlowMode(static_cast<FactoryModel::FlowMode>(selectedMode));
    }

    if(ImGui::SliderInt("Speed", &speed, 1, 10) && controller)
        controller->setSpeed(speed);

    if(ImGui::Button("Restock Now") && controller)
        controller->restockNow();

    lastActions.requestedSpeed = speed;

    ImGui::End();
}

void ControlPanelViewer::DrawStartStopButtons()
{
    if(ImGui::Button("Start"))
    {
        lastActions.startPressed = true;
        if(controller) controller->startSimulation();
    }
    ImGui::SameLine();
    if(ImGui::Button("Stop"))
    {
        lastActions.stopPressed = true;
        if(controller) controller->stopSimulation();
    }
}

void ControlPanelViewer::DrawScenarioButtons()
{
    ImGui::SameLine();
    if(ImGui::Button("Reset"))
    {
        lastActions.resetPressed = true;
        speed = 1;
        if(controller)
        {
            controller->resetSimulation();
            controller->setSpeed(speed);
        }
    }
}

#include "ControlPanelViewer.h"

void ControlPanelViewer::Draw(ImVec2 pos, ImVec2 size)
{
    lastActions = {};

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

    ImGui::SliderInt("Speed", &speed, 1, 10);
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
        if(controller) controller->resetSimulation();
    }
}

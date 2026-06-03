#include "FactoryFloorViewer.h"

void FactoryFloorViewer::Draw(ImVec2 pos, ImVec2 size)
{
    ImGui::SetNextWindowPos(pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(size, ImGuiCond_Always);
    ImGui::Begin("Factory Floor", nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse);

    ImVec2 canvasSize = ImGui::GetContentRegionAvail();
    ImDrawList* draw = ImGui::GetWindowDrawList();
    ImVec2 origin = ImGui::GetCursorScreenPos();

    draw->AddRectFilled(origin, {origin.x + canvasSize.x, origin.y + canvasSize.y}, IM_COL32(30, 30, 30, 255));
    draw->AddText({origin.x + canvasSize.x * 0.5f - 55.0f, origin.y + canvasSize.y * 0.5f},
                  IM_COL32(150, 150, 150, 255), "Factory floor placeholder");

    DrawMachines();
    DrawConveyors();

    ImGui::End();
}

void FactoryFloorViewer::DrawMachines()
{
}

void FactoryFloorViewer::DrawConveyors()
{
}




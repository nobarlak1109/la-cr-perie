#include "FactoryFloorViewer.h"
#include <string>

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
    if(!factoryModel)
        return;

    const auto& machines = factoryModel->getMachines();
    ImDrawList* draw = ImGui::GetWindowDrawList();
    ImVec2 origin = ImGui::GetCursorScreenPos();
    ImVec2 size = ImGui::GetContentRegionAvail();

    float spacing = 10.0f;
    float machineWidth = 120.0f;
    float machineHeight = 60.0f;
    float x = origin.x + spacing;
    float y = origin.y + spacing;

    for(const auto& machinePtr : machines)
    {
        if(!machinePtr)
            continue;

        ImVec2 tl = {x, y};
        ImVec2 br = {x + machineWidth, y + machineHeight};
        draw->AddRectFilled(tl, br, IM_COL32(70, 70, 130, 255));
        draw->AddRect(tl, br, IM_COL32(200, 200, 200, 255));

        std::string label = machinePtr->getName();
        if(label.empty())
            label = "Machine";

        draw->AddText({x + 8.0f, y + 8.0f}, IM_COL32(255, 255, 255, 255), label.c_str());

        x += machineWidth + spacing;
        if(x + machineWidth + spacing > origin.x + size.x)
        {
            x = origin.x + spacing;
            y += machineHeight + spacing;
        }
    }
}

void FactoryFloorViewer::DrawConveyors()
{
}




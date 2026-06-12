#include "FactoryFloorViewer.h"

#include <algorithm>
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

    for(size_t i = 0; i < machines.size(); ++i)
    {
        const auto& machinePtr = machines[i];
        if(!machinePtr)
            continue;

        ImVec2 topLeft = {x, y};
        ImVec2 bottomRight = {x + machineWidth, y + machineHeight};
        ImU32 fillColor = machinePtr->isBroken()
            ? IM_COL32(130, 50, 50, 255)
            : IM_COL32(70, 70, 130, 255);

        bool selected = selectedMachineIndex == static_cast<int>(i);
        ImU32 borderColor = selected
            ? IM_COL32(255, 220, 80, 255)
            : IM_COL32(200, 200, 200, 255);

        draw->AddRectFilled(topLeft, bottomRight, fillColor);
        draw->AddRect(topLeft, bottomRight, borderColor, 0.0f, 0, selected ? 3.0f : 1.0f);

        ImVec2 mouse = ImGui::GetMousePos();
        bool hovered =
            ImGui::IsWindowHovered() &&
            mouse.x >= topLeft.x && mouse.x <= bottomRight.x &&
            mouse.y >= topLeft.y && mouse.y <= bottomRight.y;

        if(hovered)
            draw->AddRect(topLeft, bottomRight, IM_COL32(255, 255, 255, 180), 0.0f, 0, 2.0f);

        if(hovered && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            selectedMachineIndex = static_cast<int>(i);

        std::string label = machinePtr->getName();
        if(label.empty())
            label = "Machine";

        draw->AddText({x + 8.0f, y + 8.0f}, IM_COL32(255, 255, 255, 255), label.c_str());

        float progress = std::clamp(machinePtr->getProgress(), 0.0f, 1.0f);
        ImVec2 barTopLeft = {x + 8.0f, y + machineHeight - 18.0f};
        ImVec2 barBottomRight = {x + machineWidth - 8.0f, y + machineHeight - 8.0f};
        ImVec2 barFillRight = {
            barTopLeft.x + (barBottomRight.x - barTopLeft.x) * progress,
            barBottomRight.y
        };

        ImU32 progressColor = IM_COL32(120, 120, 120, 255);
        if(machinePtr->isBroken())
            progressColor = IM_COL32(230, 70, 70, 255);
        else if(machinePtr->isRunning() && machinePtr->getQueueCount() > 0 && progress >= 0.75f)
            progressColor = IM_COL32(70, 210, 95, 255);
        else if(machinePtr->isRunning() && machinePtr->getQueueCount() > 0)
            progressColor = IM_COL32(240, 190, 70, 255);

        draw->AddRectFilled(barTopLeft, barBottomRight, IM_COL32(18, 18, 18, 255), 2.0f);
        if(progress > 0.0f)
            draw->AddRectFilled(barTopLeft, barFillRight, progressColor, 2.0f);
        draw->AddRect(barTopLeft, barBottomRight, IM_COL32(230, 230, 230, 255), 2.0f);

        std::string queueLabel = "Q:" + std::to_string(machinePtr->getQueueCount());
        draw->AddText({x + 8.0f, y + 28.0f}, IM_COL32(210, 210, 210, 255), queueLabel.c_str());

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




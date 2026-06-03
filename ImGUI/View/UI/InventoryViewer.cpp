#include "InventoryViewer.h"

void InventoryViewer::Draw(ImVec2 pos, ImVec2 size)
{
    ImGui::SetNextWindowPos(pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(size, ImGuiCond_Always);
    ImGui::Begin("Inventory", nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse);

    DrawIngredients();
    ImGui::Separator();
    DrawProducts();

    ImGui::End();
}

void InventoryViewer::DrawIngredients()
{
    ImGui::Text("-- Ingredients --");
    ImGui::Text("Eggs:           %d", data.eggs);
    ImGui::Text("Flour:          %d", data.flour);
    ImGui::Text("Milk:           %d", data.milk);
    ImGui::Text("Toppings:       %d", data.toppings);
}

void InventoryViewer::DrawProducts()
{
    ImGui::Text("-- Products --");
    ImGui::Text("Uncooked Dough: %d", data.uncookedDough);
    ImGui::Text("Cooked Dough:   %d", data.cookedDough);
    ImGui::Text("Crepes:         %d", data.crepes);
    ImGui::Text("Lost:           %d", data.lost);
}


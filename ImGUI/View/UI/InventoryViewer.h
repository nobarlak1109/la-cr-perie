#pragma once

#include "BaseViewer.h"
#include "../../Model/FactoryModel.h"

struct InventoryViewData
{
    int eggs = 0;
    int flour = 0;
    int milk = 0;
    int toppings = 0;
    int uncookedDough = 0;
    int cookedDough = 0;
    int crepes = 0;
    int lost = 0;
};

class InventoryViewer : public BaseViewer
{
public:
    explicit InventoryViewer(FactoryModel* factoryModel = nullptr) : factoryModel(factoryModel) {}

    FactoryModel* GetFactoryModel() const { return factoryModel; }
    void SetFactoryModel(FactoryModel* factoryModel) { this->factoryModel = factoryModel; }

    void SetInventory(const InventoryViewData& data) { this->data = data; }
    InventoryViewData GetInventory() const { return data; }

    void Draw(ImVec2 pos, ImVec2 size) override;
    void DrawIngredients();
    void DrawProducts();

private:
    FactoryModel* factoryModel = nullptr;
    InventoryViewData data;
};

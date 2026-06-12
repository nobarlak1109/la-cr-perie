#pragma once

#include "Dough.h"
#include "Ingredients.h"
#include "Machine.h"
#include "Product.h"

#include <memory>

class Conveyor : public Machine
{
public:
    std::string getType() const override { return "Conveyor"; }
    bool process(Inventory& inventory) override { return true; }
    void moveItem(Base* item) {}
};

class Mixer : public Machine
{
public:
    std::string getType() const override { return "Mixer"; }
    bool process(Inventory& inventory) override
    {
        inventory.addIngredient(std::make_unique<UncookedDough>());
        return true;
    }

    UncookedDough mix(Egg egg, Flour flour, Milk milk) { return UncookedDough(); }
};

class Cooker : public Machine
{
public:
    std::string getType() const override { return "Cooker"; }
    bool process(Inventory& inventory) override
    {
        inventory.addIngredient(std::make_unique<CookedDough>());
        inventory.addProduct(std::make_unique<Crepe>());
        return true;
    }

    CookedDough cook(UncookedDough dough) { return CookedDough(); }
};

class Scale : public Machine
{
public:
    std::string getType() const override { return "Scale"; }
    bool process(Inventory& inventory) override
    {
        if(inventory.getIngredientCount("Egg") < 1.0f ||
           inventory.getIngredientCount("Flour") < 1.0f ||
           inventory.getIngredientCount("Milk") < 1.0f ||
           inventory.getIngredientCount("Topping") < 1.0f)
        {
            return false;
        }

        inventory.removeIngredient("Egg", 1.0f);
        inventory.removeIngredient("Flour", 1.0f);
        inventory.removeIngredient("Milk", 1.0f);
        inventory.removeIngredient("Topping", 1.0f);
        return true;
    }

    float measure(Ingredient* ingredient) { return ingredient ? ingredient->getAmount() : 0.0f; }
};


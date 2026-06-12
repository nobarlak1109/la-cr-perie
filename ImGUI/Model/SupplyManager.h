#pragma once

#include "Base.h"
#include "Ingredients.h"
#include "Inventory.h"

#include <cstdlib>
#include <memory>
#include <string>

class SupplyManager : public Base
{
public:
    enum class SupplyMode
    {
        Normal,
        ShortSupply
    };

    void reset()
    {
        successfulRecipesSinceRestock = 0;
        shortageLogged = false;
    }

    void setSupplyMode(SupplyMode mode)
    {
        supplyMode = mode;
        successfulRecipesSinceRestock = 0;
    }

    void seedStartingInventory(Inventory& inventory, std::string& logMessage)
    {
        restockAllIngredients(inventory, 20, logMessage);
    }

    void restockNow(Inventory& inventory, std::string& logMessage)
    {
        if (supplyMode == SupplyMode::ShortSupply)
            restockRandomIngredient(inventory, 2, logMessage);
        else
            restockAllIngredients(inventory, 5, logMessage);
    }

    bool recordRecipeSuccess(Inventory& inventory, std::string& logMessage)
    {
        shortageLogged = false;
        ++successfulRecipesSinceRestock;

        if (successfulRecipesSinceRestock < 5)
            return false;

        successfulRecipesSinceRestock = 0;
        restockNow(inventory, logMessage);
        return true;
    }

    bool shouldLogShortage()
    {
        if (shortageLogged)
            return false;

        shortageLogged = true;
        return true;
    }

private:
    void restockAllIngredients(Inventory& inventory, int amount, std::string& logMessage)
    {
        for (int i = 0; i < amount; ++i)
        {
            inventory.addIngredient(std::make_unique<Egg>());
            inventory.addIngredient(std::make_unique<Flour>());
            inventory.addIngredient(std::make_unique<Milk>());
            inventory.addIngredient(std::make_unique<Topping>());
        }

        logMessage = "Supplies restocked: +" + std::to_string(amount) + " each ingredient.";
    }

    void restockRandomIngredient(Inventory& inventory, int amount, std::string& logMessage)
    {
        int type = std::rand() % 4;
        std::string name;

        for (int i = 0; i < amount; ++i)
        {
            switch (type)
            {
            case 0:
                inventory.addIngredient(std::make_unique<Egg>());
                name = "Egg";
                break;
            case 1:
                inventory.addIngredient(std::make_unique<Flour>());
                name = "Flour";
                break;
            case 2:
                inventory.addIngredient(std::make_unique<Milk>());
                name = "Milk";
                break;
            default:
                inventory.addIngredient(std::make_unique<Topping>());
                name = "Topping";
                break;
            }
        }

        logMessage = "Short supply delivery: +" + std::to_string(amount) + " " + name + ".";
    }

    SupplyMode supplyMode = SupplyMode::Normal;
    int successfulRecipesSinceRestock = 0;
    bool shortageLogged = false;
};

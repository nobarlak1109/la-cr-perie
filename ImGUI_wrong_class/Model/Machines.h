#pragma once

#include "Dough.h"
#include "Ingredients.h"
#include "Machine.h"

class Conveyor : public Machine
{
public:

    void process(Inventory& inventory) override {}
    void moveItem(Base* item) {}
};

class Mixer : public Machine
{
public:
    std::string getType() const override
    {
        return "Mixer";
    }
    void process(Inventory& inventory) override {}
    UncookedDough mix(Egg egg, Flour flour, Milk milk) { return UncookedDough(); }
};

class Cooker : public Machine
{
public:
    void process(Inventory& inventory) override {}
    CookedDough cook(UncookedDough dough) { return CookedDough(); }
};

class Scale : public Machine
{
public:
    void process(Inventory& inventory) override {}
    float measure(Ingredient* ingredient) { return ingredient ? ingredient->getAmount() : 0.0f; }
};


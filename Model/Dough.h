#pragma once

#include "Ingredient.h"

class Dough : public Ingredient
{
public:
    virtual ~Dough() = default;

    bool isCooked() const { return cooked; }
    bool getCooked() const { return cooked; }
    void setCooked(bool cooked) { this->cooked = cooked; }
    virtual std::string getType() const = 0;

protected:
    bool cooked = false;
};

class UncookedDough : public Dough
{
public:
    UncookedDough() { cooked = false; }
    std::string getType() const override { return "UncookedDough"; }
};

class CookedDough : public Dough
{
public:
    CookedDough() { cooked = true; }
    std::string getType() const override { return "CookedDough"; }
};

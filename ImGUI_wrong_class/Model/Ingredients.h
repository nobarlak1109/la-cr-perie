#pragma once

#include "Ingredient.h"

class Egg : public Ingredient
{
public:
    std::string getType() const override { return "Egg"; }
};

class Flour : public Ingredient
{
public:
    std::string getType() const override { return "Flour"; }
};

class Milk : public Ingredient
{
public:
    std::string getType() const override { return "Milk"; }
};

class Topping : public Ingredient
{
public:
    std::string getType() const override { return "Topping"; }
};


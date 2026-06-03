#pragma once

#include "Base.h"

class Ingredient : public Base
{
public:
    virtual ~Ingredient() = default;

    float getAmount() const { return amount; }
    void setAmount(float amount) { this->amount = amount; }
    virtual std::string getType() const = 0;

protected:
    float amount = 0.0f;
};


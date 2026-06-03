#pragma once

#include "Base.h"

class Product : public Base
{
public:
    virtual ~Product() = default;

    float getQuality() const { return quality; }
    void setQuality(float quality) { this->quality = quality; }
    virtual std::string getProductName() const = 0;

protected:
    float quality = 0.0f;
};

class Crepe : public Product
{
public:
    std::string getProductName() const override { return "Crepe"; }
};


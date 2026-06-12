#pragma once

#include "Base.h"
#include "Ingredient.h"
#include "Product.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

class Inventory : public Base
{
public:
    Inventory() = default;
    Inventory(const Inventory&) = delete;
    Inventory& operator=(const Inventory&) = delete;
    Inventory(Inventory&&) = default;
    Inventory& operator=(Inventory&&) = default;

    void addIngredient(std::unique_ptr<Ingredient> ingredient) { ingredients.push_back(std::move(ingredient)); }
    const std::vector<std::unique_ptr<Ingredient>>& getIngredients() const { return ingredients; }
    void setIngredients(std::vector<std::unique_ptr<Ingredient>> ingredients)
    {
        this->ingredients = std::move(ingredients);
    }

    void removeIngredient(const std::string& type, float amount)
    {
        float remaining = amount;

        for (auto it = ingredients.begin(); it != ingredients.end() && remaining > 0.0f;)
        {
            if (*it && (*it)->getType() == type)
            {
                remaining -= 1.0f;
                it = ingredients.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    void addProduct(std::unique_ptr<Product> product) { products.push_back(std::move(product)); }
    const std::vector<std::unique_ptr<Product>>& getProducts() const { return products; }
    void setProducts(std::vector<std::unique_ptr<Product>> products)
    {
        this->products = std::move(products);
    }

    float getIngredientCount(const std::string& type) const
    {
        float count = 0.0f;
        for (const auto& ingredient : ingredients)
        {
            if (ingredient && ingredient->getType() == type)
                count += 1.0f;
        }
        return count;
    }

    int getProductCount(const std::string& type) const
    {
        int count = 0;
        for (const auto& product : products)
        {
            if (product && product->getProductName() == type)
                ++count;
        }
        return count;
    }

private:
    std::vector<std::unique_ptr<Ingredient>> ingredients;
    std::vector<std::unique_ptr<Product>> products;
};

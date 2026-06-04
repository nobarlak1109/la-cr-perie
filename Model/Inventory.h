#pragma once

#include "Ingredient.h"
#include "Product.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

class Inventory
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

    void removeIngredient(const std::string& type, float amount) {}
    void addProduct(std::unique_ptr<Product> product) { products.push_back(std::move(product)); }
    const std::vector<std::unique_ptr<Product>>& getProducts() const { return products; }
    void setProducts(std::vector<std::unique_ptr<Product>> products)
    {
        this->products = std::move(products);
    }

    float getIngredientCount(const std::string& type) const { return 0.0f; }
    int getProductCount(const std::string& type) const { return 0; }

private:
    std::vector<std::unique_ptr<Ingredient>> ingredients;
    std::vector<std::unique_ptr<Product>> products;
};

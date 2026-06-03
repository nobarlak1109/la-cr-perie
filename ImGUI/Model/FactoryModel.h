#pragma once

#include "Base.h"
#include "Inventory.h"
#include "Machine.h"
#include "Product.h"

#include <memory>
#include <utility>
#include <vector>

class FactoryModel : public Base
{
public:
    FactoryModel() = default;
    FactoryModel(const FactoryModel&) = delete;
    FactoryModel& operator=(const FactoryModel&) = delete;
    FactoryModel(FactoryModel&&) = default;
    FactoryModel& operator=(FactoryModel&&) = default;

    void startFactory() { running = true; }
    void stopFactory() { running = false; }
    void update(float deltaTime) {}

    bool isRunning() const { return running; }
    bool getRunning() const { return running; }
    void setRunning(bool running) { this->running = running; }

    void addMachine(std::unique_ptr<Machine> machine) { machines.push_back(std::move(machine)); }
    const std::vector<std::unique_ptr<Machine>>& getMachines() const { return machines; }
    void setMachines(std::vector<std::unique_ptr<Machine>> machines)
    {
        this->machines = std::move(machines);
    }

    Inventory& getInventory() { return inventory; }
    const Inventory& getInventory() const { return inventory; }
    void setInventory(Inventory inventory) { this->inventory = std::move(inventory); }

    void addFinishedProduct(std::unique_ptr<Product> product) { finishedProducts.push_back(std::move(product)); }
    const std::vector<std::unique_ptr<Product>>& getFinishedProducts() const { return finishedProducts; }
    void setFinishedProducts(std::vector<std::unique_ptr<Product>> finishedProducts)
    {
        this->finishedProducts = std::move(finishedProducts);
    }

private:
    bool running = false;
    std::vector<std::unique_ptr<Machine>> machines;
    Inventory inventory;
    std::vector<std::unique_ptr<Product>> finishedProducts;
};

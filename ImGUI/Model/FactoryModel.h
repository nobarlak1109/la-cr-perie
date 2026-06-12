#pragma once

#include "Base.h"
#include "FactoryLogger.h"
#include "FactoryTypes.h"
#include "Inventory.h"
#include "Machine.h"
#include "Product.h"
#include "ProductionManager.h"
#include "ScenarioManager.h"
#include "SupplyManager.h"
#include "Worker.h"
#include "WorkerDispatcher.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

class FactoryModel : public Base
{
public:
    using FlowMode = FactoryFlowMode;

    FactoryModel() = default;
    FactoryModel(const FactoryModel&) = delete;
    FactoryModel& operator=(const FactoryModel&) = delete;
    FactoryModel(FactoryModel&&) = default;
    FactoryModel& operator=(FactoryModel&&) = default;

    void startFactory()
    {
        running = true;
        for (auto& machine : machines)
            machine->start();
    }

    void stopFactory()
    {
        running = false;
        for (auto& machine : machines)
            machine->stop();
    }

    void resetFactory()
    {
        stopFactory();
        inventory = Inventory();
        finishedProducts.clear();
        lostItems = 0;
        supplyManager.reset();
        logger.clear();
        scenarioManager.setFlowMode(FlowMode::Normal);
        supplyManager.setSupplyMode(SupplyManager::SupplyMode::Normal);
        seedStartingInventory();

        for (auto& machine : machines)
            machine->resetRuntimeState();
    }

    void update(float deltaTime)
    {
        if (!running)
            return;

        for (auto& machine : machines)
        {
            if (machine->isSourceMachine() && machine->getQueueCount() == 0)
                machine->addItem();
        }

        workerDispatcher.updateWorkers(machines, workers, logger, deltaTime);
        scenarioManager.updateMachines(
            machines,
            inventory,
            supplyManager,
            logger,
            productionManager,
            lostItems,
            deltaTime);
        workerDispatcher.dispatchWorkers(machines, workers);
    }

    bool isRunning() const { return running; }
    bool getRunning() const { return running; }
    void setRunning(bool running) { this->running = running; }

    void setFlowMode(FlowMode mode)
    {
        scenarioManager.setFlowMode(mode);
        supplyManager.setSupplyMode(mode == FlowMode::ShortSupply
            ? SupplyManager::SupplyMode::ShortSupply
            : SupplyManager::SupplyMode::Normal);
        addLog(mode == FlowMode::ShortSupply ? "Scenario: Short Supply." : "Scenario changed.");
    }
    FlowMode getFlowMode() const { return scenarioManager.getFlowMode(); }

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

    void addWorker(std::unique_ptr<Worker> worker) { workers.push_back(std::move(worker)); }
    const std::vector<std::unique_ptr<Worker>>& getWorkers() const { return workers; }

    void addLostItem() { ++lostItems; }
    int getLostItems() const { return lostItems; }

    void seedStartingInventory()
    {
        std::string logMessage;
        supplyManager.seedStartingInventory(inventory, logMessage);
        addLog(logMessage);
    }

    void restockNow()
    {
        std::string logMessage;
        supplyManager.restockNow(inventory, logMessage);
        addLog(logMessage);
    }

    void addLog(const std::string& message)
    {
        logger.addLog(message);
    }

    const std::vector<std::string>& getLogs() const { return logger.getLogs(); }

private:
    bool running = false;
    int lostItems = 0;
    std::vector<std::unique_ptr<Machine>> machines;
    std::vector<std::unique_ptr<Worker>> workers;
    Inventory inventory;
    ProductionManager productionManager;
    ScenarioManager scenarioManager;
    SupplyManager supplyManager;
    WorkerDispatcher workerDispatcher;
    FactoryLogger logger;
    std::vector<std::unique_ptr<Product>> finishedProducts;
};

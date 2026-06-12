#pragma once

#include "Base.h"
#include "Inventory.h"
#include "Machine.h"
#include "Product.h"
#include "Worker.h"

#include <memory>
#include <vector>
#include <utility>
#include <cstdlib>

class FactoryModel : public Base
{
public:
    enum class FlowMode
    {
        Normal = 0,
        Bottleneck = 1,
        RandomBreakdown = 2,
        Overflow = 3
    };

    FactoryModel() = default;

    FactoryModel(const FactoryModel&) = delete;
    FactoryModel& operator=(const FactoryModel&) = delete;
    FactoryModel(FactoryModel&&) = default;
    FactoryModel& operator=(FactoryModel&&) = default;

    // ---------------- WORKERS ----------------
    void addWorker(std::unique_ptr<Worker> worker)
    {
        workers.push_back(std::move(worker));
    }

    const std::vector<std::unique_ptr<Worker>>& getWorkers() const
    {
        return workers;
    }

    // ---------------- FACTORY CONTROL ----------------
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
        finishedProducts.clear();
        lostItems = 0;
        flowMode = FlowMode::Normal;
    }

    // ---------------- MAIN UPDATE ----------------
    void update(float deltaTime)
    {
        if (!running)
            return;

        // keep source machines fed
        for (auto& machine : machines)
        {
            if (machine->isSourceMachine() &&
                machine->getQueueCount() == 0)
            {
                machine->addItem();
            }
        }

        // update workers first
        for (auto& worker : workers)
        {
            worker->update(deltaTime);
        }

        // ---------------- FLOW MODES ----------------
        switch (flowMode)
        {
        case FlowMode::Normal:
        {
            for (auto& machine : machines)
                machine->update(deltaTime);
            break;
        }

        case FlowMode::Bottleneck:
        {
            for (size_t i = 0; i < machines.size(); ++i)
            {
                if (i == 2)
                    machines[i]->update(deltaTime * 0.25f);
                else
                    machines[i]->update(deltaTime);
            }
            break;
        }

        case FlowMode::RandomBreakdown:
        {
            for (auto& machine : machines)
            {
                machine->update(deltaTime);

                if (machine->hasJustFinishedItem())
                {
                    if ((std::rand() % 100) < 6)
                    {
                        machine->setBroken(true);
                    }
                }
            }
            break;
        }

        case FlowMode::Overflow:
        {
            for (auto& machine : machines)
            {
                float speedMultiplier = 1.0f;
            
                if (machine->getType() == "Mixer")
                    speedMultiplier = 0.3f;
            
                machine->update(deltaTime * speedMultiplier);
            
                int overflow =
                    machine->getQueueCount() - machine->getMaxQueueSize();
            
                if (overflow > 0)
                {
                    for (int i = 0; i < overflow; i++)
                        addLostItem();
                
                    machine->removeItemsFromQueue(overflow);
                }
            }
            break;
        }
        }

        // ---------------- WORKER DISPATCH ----------------
        for (auto& machine : machines)
        {
            if (!machine->isBroken())
                continue;

            for (auto& worker : workers)
            {
                if (!worker->isBusy())
                {
                    worker->assignMachine(machine.get());
                    break;
                }
            }
        }
    }

    // ---------------- GETTERS / SETTERS ----------------
    bool isRunning() const { return running; }
    bool getRunning() const { return running; }

    void setRunning(bool running) { this->running = running; }

    void setFlowMode(FlowMode mode) { flowMode = mode; }

    FlowMode getFlowMode() const { return flowMode; }

    void addMachine(std::unique_ptr<Machine> machine)
    {
        machines.push_back(std::move(machine));
    }

    const std::vector<std::unique_ptr<Machine>>& getMachines() const
    {
        return machines;
    }

    void setMachines(std::vector<std::unique_ptr<Machine>> m)
    {
        machines = std::move(m);
    }

    Inventory& getInventory() { return inventory; }
    const Inventory& getInventory() const { return inventory; }

    void setInventory(Inventory inv) { inventory = std::move(inv); }

    void addFinishedProduct(std::unique_ptr<Product> product)
    {
        finishedProducts.push_back(std::move(product));
    }

    const std::vector<std::unique_ptr<Product>>& getFinishedProducts() const
    {
        return finishedProducts;
    }

    void setFinishedProducts(std::vector<std::unique_ptr<Product>> fp)
    {
        finishedProducts = std::move(fp);
    }

    void addLostItem() { ++lostItems; }

    int getLostItems() const { return lostItems; }

private:
    bool running = false;
    int lostItems = 0;

    FlowMode flowMode = FlowMode::Normal;

    std::vector<std::unique_ptr<Machine>> machines;
    std::vector<std::unique_ptr<Worker>> workers;

    Inventory inventory;
    std::vector<std::unique_ptr<Product>> finishedProducts;
};
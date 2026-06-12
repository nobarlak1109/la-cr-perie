#pragma once

#include "Base.h"
#include "FactoryLogger.h"
#include "FactoryTypes.h"
#include "Inventory.h"
#include "Machine.h"
#include "ProductionManager.h"
#include "SupplyManager.h"

#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

class ScenarioManager : public Base
{
public:
    void setFlowMode(FactoryFlowMode mode)
    {
        flowMode = mode;
    }

    FactoryFlowMode getFlowMode() const
    {
        return flowMode;
    }

    void updateMachines(
        std::vector<std::unique_ptr<Machine>>& machines,
        Inventory& inventory,
        SupplyManager& supplyManager,
        FactoryLogger& logger,
        ProductionManager& productionManager,
        int& lostItems,
        float deltaTime)
    {
        switch (flowMode)
        {
        case FactoryFlowMode::Normal:
        case FactoryFlowMode::ShortSupply:
            productionManager.updateMachines(machines, inventory, supplyManager, logger, deltaTime);
            break;

        case FactoryFlowMode::Bottleneck:
            updateBottleneck(machines, inventory, supplyManager, logger, productionManager, deltaTime);
            break;

        case FactoryFlowMode::RandomBreakdown:
            updateRandomBreakdown(machines, inventory, supplyManager, logger, productionManager, deltaTime);
            break;

        case FactoryFlowMode::Overflow:
            updateOverflow(machines, inventory, supplyManager, logger, productionManager, lostItems, deltaTime);
            break;
        }
    }

private:
    void updateBottleneck(
        std::vector<std::unique_ptr<Machine>>& machines,
        Inventory& inventory,
        SupplyManager& supplyManager,
        FactoryLogger& logger,
        ProductionManager& productionManager,
        float deltaTime)
    {
        for (size_t i = 0; i < machines.size(); ++i)
            productionManager.updateMachine(
                *machines[i],
                inventory,
                supplyManager,
                logger,
                i == 2 ? deltaTime * 0.25f : deltaTime);
    }

    void updateRandomBreakdown(
        std::vector<std::unique_ptr<Machine>>& machines,
        Inventory& inventory,
        SupplyManager& supplyManager,
        FactoryLogger& logger,
        ProductionManager& productionManager,
        float deltaTime)
    {
        for (auto& machine : machines)
        {
            productionManager.updateMachine(*machine, inventory, supplyManager, logger, deltaTime);

            if (machine->hasJustFinishedItem() && (std::rand() % 100) < 6)
            {
                machine->setBroken(true);
                addMachineLog(*machine, "broken!", logger);
            }
        }
    }

    void updateOverflow(
        std::vector<std::unique_ptr<Machine>>& machines,
        Inventory& inventory,
        SupplyManager& supplyManager,
        FactoryLogger& logger,
        ProductionManager& productionManager,
        int& lostItems,
        float deltaTime)
    {
        for (auto& machine : machines)
        {
            float speedMultiplier = machine->getType() == "Mixer" ? 0.3f : 1.0f;
            productionManager.updateMachine(*machine, inventory, supplyManager, logger, deltaTime * speedMultiplier);

            int overflow = machine->getQueueCount() - machine->getMaxQueueSize();
            if (overflow > 0)
            {
                lostItems += overflow;
                machine->removeItemsFromQueue(overflow);
            }
        }
    }

    void addMachineLog(const Machine& machine, const std::string& event, FactoryLogger& logger)
    {
        std::string name = machine.getName();
        if (name.empty())
            name = machine.getType();

        logger.addLog(name + " " + event);
    }

    FactoryFlowMode flowMode = FactoryFlowMode::Normal;
};

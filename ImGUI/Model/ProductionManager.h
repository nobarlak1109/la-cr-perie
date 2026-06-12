#pragma once

#include "Base.h"
#include "FactoryLogger.h"
#include "Inventory.h"
#include "Machine.h"
#include "SupplyManager.h"

#include <memory>
#include <string>
#include <vector>

class ProductionManager : public Base
{
public:
    void updateMachines(
        std::vector<std::unique_ptr<Machine>>& machines,
        Inventory& inventory,
        SupplyManager& supplyManager,
        FactoryLogger& logger,
        float deltaTime)
    {
        for (auto& machine : machines)
            updateMachine(*machine, inventory, supplyManager, logger, deltaTime);
    }

    void updateMachine(
        Machine& machine,
        Inventory& inventory,
        SupplyManager& supplyManager,
        FactoryLogger& logger,
        float deltaTime)
    {
        machine.update(deltaTime, inventory);

        if (machine.hasFailedProcess() && machine.getType() == "Scale")
        {
            if (supplyManager.shouldLogShortage())
                logger.addLog("Short supply: not enough ingredients.");
            return;
        }

        if (!machine.hasJustFinishedItem())
            return;

        std::string type = machine.getType();
        if (type == "Scale")
        {
            logger.addLog("Ingredients Scaled!");

            std::string logMessage;
            if (supplyManager.recordRecipeSuccess(inventory, logMessage))
                logger.addLog(logMessage);
        }
        else if (type == "Mixer")
        {
            logger.addLog("Dough mixed!");
        }
        else if (type == "Cooker")
        {
            logger.addLog("Crepe made!");
        }
    }
};

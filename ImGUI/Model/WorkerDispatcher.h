#pragma once

#include "Base.h"
#include "FactoryLogger.h"
#include "Machine.h"
#include "Worker.h"

#include <memory>
#include <string>
#include <vector>

class WorkerDispatcher : public Base
{
public:
    void updateWorkers(
        std::vector<std::unique_ptr<Machine>>& machines,
        std::vector<std::unique_ptr<Worker>>& workers,
        FactoryLogger& logger,
        float deltaTime)
    {
        std::vector<bool> wasBroken;
        wasBroken.reserve(machines.size());

        for (const auto& machine : machines)
            wasBroken.push_back(machine && machine->isBroken());

        for (auto& worker : workers)
            worker->update(deltaTime);

        for (size_t i = 0; i < machines.size(); ++i)
        {
            if (wasBroken[i] && machines[i] && !machines[i]->isBroken())
                addMachineLog(*machines[i], "fixed!", logger);
        }
    }

    void dispatchWorkers(
        std::vector<std::unique_ptr<Machine>>& machines,
        std::vector<std::unique_ptr<Worker>>& workers)
    {
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

private:
    void addMachineLog(const Machine& machine, const std::string& event, FactoryLogger& logger)
    {
        std::string name = machine.getName();
        if (name.empty())
            name = machine.getType();

        logger.addLog(name + " " + event);
    }
};

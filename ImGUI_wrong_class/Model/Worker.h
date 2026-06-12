#pragma once

#include "Base.h"
#include "Machine.h"

class Worker : public Base
{
public:
    void assignMachine(Machine* machine)
    {
        if (!busy && machine)
        {
            assignedMachine = machine;
            repairTimer = 3.0f;
            busy = true;
        }
    }

    void update(float deltaTime)
    {
        if (!busy)
            return;

        repairTimer -= deltaTime;

        if (repairTimer <= 0.0f)
        {
            if (assignedMachine)
            {
                assignedMachine->repair();
            }

            assignedMachine = nullptr;
            busy = false;
        }
    }

    bool isBusy() const
    {
        return busy;
    }

private:
    bool busy = false;
    float repairTimer = 0.0f;
    Machine* assignedMachine = nullptr;
};
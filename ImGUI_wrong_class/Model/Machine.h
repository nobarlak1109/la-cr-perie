#pragma once

#include "Base.h"
#include "Inventory.h"

class Machine : public Base
{
public:
    virtual ~Machine() = default;

    virtual void start()
    {
        running = true;
    }

    virtual void stop()
    {
        running = false;
    }

    virtual void update(float deltaTime)
{
    finishedItemThisUpdate = false;

    if (!running || broken)
        return;

    if (queueCount <= 0)
    {
        progress = 0.0f;
        return;
    }

    progress += deltaTime;

    if (progress >= 1.0f)
    {
        progress = 0.0f;

        process(dummyInventory);

        --queueCount;
        ++itemsProcessed;

        finishedItemThisUpdate = true;

        if (nextMachine)
        {
            nextMachine->addItem();
        }
    }
}   
    virtual void process(Inventory& inventory) = 0;

    bool isRunning() const
    {
        return running;
    }

    float getProgress() const
    {
        return progress;
    }

    void setProgress(float progress)
    {
        this->progress = progress;
    }

   bool addItem()
    {
        ++queueCount;   // ALWAYS accept
        return true;
    }

    int getMaxQueueSize() const
    {
        return maxQueueSize;
    }

    void setMaxQueueSize(int size)
    {
        maxQueueSize = size;
    }

    void removeItem()
    {
        if (queueCount > 0)
            --queueCount;
    }

    int getQueueCount() const
    {
        return queueCount;
    }
    void removeItemsFromQueue(int amount)
    {
        queueCount -= amount;
        if (queueCount < 0)
            queueCount = 0;
    }
    void setNextMachine(Machine* next)
    {
        nextMachine = next;
    }

    Machine* getNextMachine() const
    {
        return nextMachine;
    }

    void setSourceMachine(bool value)
    {
        sourceMachine = value;
    }

    bool isSourceMachine() const
    {
        return sourceMachine;
    }
    int getItemsProcessed() const
    {
        return itemsProcessed;
    }
    bool isBroken() const
    {
        return broken;
    }

    void setBroken(bool value)
    {
        broken = value;
    }

    void repair()
    {
        broken = false;
    }
    bool hasJustFinishedItem() const
    {
        return finishedItemThisUpdate;
    }
    virtual std::string getType() const
    {
        return "Machine";
    }
protected:
    bool running = false;
    bool broken = false;
    float progress = 0.0f;
    int itemsProcessed = 0;
    int queueCount = 0;
    bool finishedItemThisUpdate = false;
    bool sourceMachine = false;
    int maxQueueSize = 10;

    Machine* nextMachine = nullptr;

    Inventory dummyInventory;
};
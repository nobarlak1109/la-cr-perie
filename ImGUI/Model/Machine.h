#pragma once

#include "Base.h"
#include "Inventory.h"

class Machine : public Base
{
public:
    virtual ~Machine() = default;

    virtual void start() { running = true; }
    virtual void stop() { running = false; }

    virtual void update(float deltaTime)
    {
        update(deltaTime, dummyInventory);
    }

    virtual void update(float deltaTime, Inventory& inventory)
    {
        finishedItemThisUpdate = false;
        failedProcessThisUpdate = false;

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
            if (!process(inventory))
            {
                failedProcessThisUpdate = true;
                return;
            }

            --queueCount;
            ++itemsProcessed;
            finishedItemThisUpdate = true;

            if (nextMachine)
                nextMachine->addItem();
        }
    }

    virtual bool process(Inventory& inventory) = 0;
    virtual std::string getStatus() const { return broken ? "Broken" : (running ? "Running" : "Idle"); }
    virtual std::string getType() const { return "Machine"; }

    bool isRunning() const { return running; }
    bool getRunning() const { return running; }
    void setRunning(bool running) { this->running = running; }

    float getProgress() const { return progress; }
    void setProgress(float progress) { this->progress = progress; }

    bool addItem()
    {
        ++queueCount;
        return queueCount <= maxQueueSize;
    }

    void removeItem()
    {
        if (queueCount > 0)
            --queueCount;
    }

    void removeItemsFromQueue(int amount)
    {
        queueCount -= amount;
        if (queueCount < 0)
            queueCount = 0;
    }

    int getQueueCount() const { return queueCount; }
    int getItemsProcessed() const { return itemsProcessed; }

    int getMaxQueueSize() const { return maxQueueSize; }
    void setMaxQueueSize(int size) { maxQueueSize = size > 0 ? size : 1; }

    void setNextMachine(Machine* next) { nextMachine = next; }
    Machine* getNextMachine() const { return nextMachine; }

    void setSourceMachine(bool value) { sourceMachine = value; }
    bool isSourceMachine() const { return sourceMachine; }

    bool isBroken() const { return broken; }
    void setBroken(bool value) { broken = value; }
    void repair() { broken = false; }
    bool hasJustFinishedItem() const { return finishedItemThisUpdate; }
    bool hasFailedProcess() const { return failedProcessThisUpdate; }

    void resetRuntimeState()
    {
        running = false;
        broken = false;
        progress = 0.0f;
        itemsProcessed = 0;
        queueCount = 0;
        finishedItemThisUpdate = false;
        failedProcessThisUpdate = false;
    }

protected:
    bool running = false;
    bool broken = false;
    float progress = 0.0f;
    int itemsProcessed = 0;
    int queueCount = 0;
    bool finishedItemThisUpdate = false;
    bool failedProcessThisUpdate = false;
    bool sourceMachine = false;
    int maxQueueSize = 10;
    Machine* nextMachine = nullptr;
    Inventory dummyInventory;
};

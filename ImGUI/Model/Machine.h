#pragma once

#include "Base.h"
#include "Inventory.h"

class Machine : public Base
{
public:
    virtual ~Machine() = default;

    virtual void start() { running = true; }
    virtual void stop() { running = false; }
    virtual void update(float deltaTime) {}
    virtual void process(Inventory& inventory) = 0;
    virtual std::string getStatus() const { return running ? "Running" : "Idle"; }

    bool isRunning() const { return running; }
    bool getRunning() const { return running; }
    void setRunning(bool running) { this->running = running; }

    float getProgress() const { return progress; }
    void setProgress(float progress) { this->progress = progress; }

protected:
    bool running = false;
    float progress = 0.0f;
};

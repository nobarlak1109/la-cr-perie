#pragma once

#include "../Model/FactoryModel.h"
#include "BaseController.h"

class FactoryController : public BaseController
{
public:
    explicit FactoryController(FactoryModel* factory = nullptr) : factory(factory) {}

    FactoryModel* getFactory() const { return factory; }
    void setFactory(FactoryModel* factory) { this->factory = factory; }

    void startSimulation()
    {
        if(factory) factory->startFactory();
    }

    void stopSimulation()
    {
        if(factory) factory->stopFactory();
    }

    void resetSimulation()
    {
        if(factory) factory->resetFactory();
        speed = 1;
    }

    void setSpeed(int newSpeed)
    {
        speed = newSpeed > 0 ? newSpeed : 1;
    }

    int getSpeed() const { return speed; }

    void setFlowMode(FactoryModel::FlowMode mode)
    {
        if(factory) factory->setFlowMode(mode);
    }

    FactoryModel::FlowMode getFlowMode() const
    {
        return factory ? factory->getFlowMode() : FactoryModel::FlowMode::Normal;
    }

    void restockNow()
    {
        if(factory) factory->restockNow();
    }

    void update(float deltaTime) override
    {
        if(factory) factory->update(deltaTime * static_cast<float>(speed));
    }

    void runScenario() {}

    int getLostItems() const { return factory ? factory->getLostItems() : 0; }
    const std::vector<std::unique_ptr<Machine>>& getMachines() const { return factory->getMachines(); }
    const Inventory& getInventory() const { return factory->getInventory(); }

private:
    FactoryModel* factory = nullptr;
    int speed = 1;
};

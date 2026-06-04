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

    void resetSimulation() {}

    void update(float deltaTime) override
    {
        if(factory) factory->update(deltaTime);
    }

    void runScenario() {}

private:
    FactoryModel* factory = nullptr;
};

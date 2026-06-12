#include "View.h"
#include "../Model/Ingredients.h"
#include "../Model/Machines.h"

#include <chrono>
#include <memory>

View::View()
    : factoryController(&factoryModel),
      dashboard(&factoryModel, &factoryController)
{
    auto scale = std::make_unique<Scale>();
    scale->setName("Scale");

    auto conveyor1 = std::make_unique<Conveyor>();
    conveyor1->setName("Conveyor 1");

    auto mixer = std::make_unique<Mixer>();
    mixer->setName("Mixer");

    auto conveyor2 = std::make_unique<Conveyor>();
    conveyor2->setName("Conveyor 2");

    auto cooker = std::make_unique<Cooker>();
    cooker->setName("Cooker");

    scale->setNextMachine(conveyor1.get());
    conveyor1->setNextMachine(mixer.get());
    mixer->setNextMachine(conveyor2.get());
    conveyor2->setNextMachine(cooker.get());

    scale->setSourceMachine(true);
    scale->addItem();

    factoryModel.addMachine(std::move(scale));
    factoryModel.addMachine(std::move(conveyor1));
    factoryModel.addMachine(std::move(mixer));
    factoryModel.addMachine(std::move(conveyor2));
    factoryModel.addMachine(std::move(cooker));

    auto worker = std::make_unique<Worker>();
    worker->setName("Worker 1");
    factoryModel.addWorker(std::move(worker));

    factoryModel.seedStartingInventory();
}

bool View::Init()
{
    return platform.Init("Crêperie", 1280, 800);
}

void View::Run()
{
    using clock = std::chrono::steady_clock;
    auto lastTime = clock::now();

    bool running = true;
    while(running)
    {
        auto now = clock::now();
        float deltaTime = std::chrono::duration<float>(now - lastTime).count();
        lastTime = now;

        running = platform.PollEvents();
        platform.NewFrame();

        factoryController.update(deltaTime);
        dashboard.DrawAll();

        platform.Render();
    }
}

void View::Shutdown()
{
    platform.Shutdown();
}

#include "View.h"
#include "../Model/Machines.h"
#include <memory>
#include <chrono>

View::View()
    : factoryController(&factoryModel),
      dashboard(&factoryModel, &factoryController)
{
    auto s1 = std::make_unique<Scale>();
    s1->setName("Scale");

    auto c1 = std::make_unique<Conveyor>();
    c1->setName("Conveyor 1");

    auto m1 = std::make_unique<Mixer>();
    m1->setName("Mixer");

    auto c2 = std::make_unique<Conveyor>();
    c2->setName("Conveyor 2");

    auto k1 = std::make_unique<Cooker>();
    k1->setName("Cooker");

    // Connect pipeline
    s1->setNextMachine(c1.get());
    c1->setNextMachine(m1.get());
    m1->setNextMachine(c2.get());
    c2->setNextMachine(k1.get());

    // Mark source
    s1->setSourceMachine(true);

    // IMPORTANT: start machines so update() actually runs
    s1->start();
    c1->start();
    m1->start();
    c2->start();
    k1->start();

    // Seed first item so pipeline is active immediately
    s1->addItem();

    // Add machines to model FIRST
    factoryModel.addMachine(std::move(s1));
    factoryModel.addMachine(std::move(c1));
    factoryModel.addMachine(std::move(m1));
    factoryModel.addMachine(std::move(c2));
    factoryModel.addMachine(std::move(k1));

    // Worker system (optional but now properly initialized)
    auto worker = std::make_unique<Worker>();
    worker->setName("Worker 1");

    factoryModel.addWorker(std::move(worker));

    // Seed inventory (UI only)
    factoryModel.getInventory().addIngredient(std::make_unique<Egg>());
    factoryModel.getInventory().addIngredient(std::make_unique<Flour>());
    factoryModel.getInventory().addIngredient(std::make_unique<Milk>());
    factoryModel.getInventory().addIngredient(std::make_unique<Topping>());
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

    while (running)
    {
        auto now = clock::now();

        float deltaTime =
            std::chrono::duration<float>(now - lastTime).count();

        lastTime = now;

        running = platform.PollEvents();

        platform.NewFrame();

        // ONLY controller drives simulation (correct architecture)
        factoryController.update(deltaTime);

        dashboard.DrawAll();

        platform.Render();
    }
}

void View::Shutdown()
{
    platform.Shutdown();
}
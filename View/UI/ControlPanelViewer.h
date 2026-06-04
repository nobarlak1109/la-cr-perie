#pragma once

#include "BaseViewer.h"
#include "../../Controller/FactoryController.h"

struct ControlActions
{
    bool startPressed = false;
    bool stopPressed = false;
    bool resetPressed = false;
    int requestedSpeed = 1;
};

class ControlPanelViewer : public BaseViewer
{
public:
    explicit ControlPanelViewer(FactoryController* controller = nullptr) : controller(controller) {}

    FactoryController* GetController() const { return controller; }
    void SetController(FactoryController* controller) { this->controller = controller; }

    void Draw(ImVec2 pos, ImVec2 size) override;
    ControlActions GetActions() const { return lastActions; }

private:
    void DrawStartStopButtons();
    void DrawScenarioButtons();

    FactoryController* controller = nullptr;
    int speed = 1;
    ControlActions lastActions;
};

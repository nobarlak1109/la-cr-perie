#pragma once

#include "imgui.h"

class BaseViewer
{
public:
    virtual ~BaseViewer() = default;
    virtual void Draw(ImVec2 pos, ImVec2 size) = 0;
};


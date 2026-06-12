#pragma once

#include "../../Model/Base.h"
#include "imgui.h"

class BaseViewer : public Base
{
public:
    virtual ~BaseViewer() = default;
    virtual void Draw(ImVec2 pos, ImVec2 size) = 0;
};


#pragma once

#include "../Model/Base.h"

class BaseController : public Base
{
public:
    virtual ~BaseController() = default;
    virtual void update(float deltaTime) = 0;
};


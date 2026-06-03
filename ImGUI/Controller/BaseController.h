#pragma once

class BaseController
{
public:
    virtual ~BaseController() = default;
    virtual void update(float deltaTime) = 0;
};


#pragma once

#include "Base.h"
#include "Machine.h"

class Inspector : public Base
{
public:
    void process(Machine& machine) {}
    bool inspect(Machine* machine) { return machine != nullptr; }
};

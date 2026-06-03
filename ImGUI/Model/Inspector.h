#pragma once

#include "Machine.h"

class Inspector
{
public:
    void process(Machine& machine) {}
    bool inspect(Machine* machine) { return machine != nullptr; }
};

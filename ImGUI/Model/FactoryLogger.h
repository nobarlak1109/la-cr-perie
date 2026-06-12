#pragma once

#include "Base.h"

#include <string>
#include <vector>

class FactoryLogger : public Base
{
public:
    void addLog(const std::string& message)
    {
        logs.push_back(message);
        if (logs.size() > maxLogCount)
            logs.erase(logs.begin());
    }

    void clear()
    {
        logs.clear();
    }

    const std::vector<std::string>& getLogs() const
    {
        return logs;
    }

private:
    static constexpr size_t maxLogCount = 80;
    std::vector<std::string> logs;
};

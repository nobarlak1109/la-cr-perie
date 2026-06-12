#pragma once

#include <string>

class Base
{
public:
    Base() = default;
    Base(int id, const std::string& name) : id(id), name(name) {}
    virtual ~Base() = default;

    int getId() const { return id; }
    void setId(int id) { this->id = id; }
    std::string getName() const { return name; }
    void setName(const std::string& name) { this->name = name; }

protected:
    int id = 0;
    std::string name;
};

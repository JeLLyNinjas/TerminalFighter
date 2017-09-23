#pragma once

#include <yaml-cpp/yaml.h>

class string;

class I_Settings {
public:
    virtual void parseDocument(const std::string& path) = 0;
};
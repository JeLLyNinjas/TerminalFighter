#include <string>
#include <iostream>

#include <yaml-cpp/yaml.h>

#include "Settings.h"

void Settings::parseDocument(const std::string& path) {
    YAML::Node config = YAML::LoadFile(path);
    std::cout << config["test"] << " OMG SETTINGS" << std::endl;
}

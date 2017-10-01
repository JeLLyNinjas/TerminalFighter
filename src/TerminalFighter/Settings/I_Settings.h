#pragma once

#include <yaml-cpp/yaml.h>

class string;


class I_Settings {
public:
    virtual bool reload_settings() = 0;
    virtual const YAML::Node& video_settings() const = 0;
    virtual const YAML::Node& asset_paths() const = 0;
};
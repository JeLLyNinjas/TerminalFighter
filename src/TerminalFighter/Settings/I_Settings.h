#pragma once

#include <yaml-cpp/yaml.h>

enum class SettingsGroup {
    VIDEO_SETTINGS,
    ASSET_PATHS
};

class I_Settings {
public:
    virtual bool reload_all_settings() = 0;
    virtual bool load_string(
        SettingsGroup group,
        std::vector<std::string> keys,
        std::string& value) const = 0;
    virtual const YAML::Node& video_settings() const = 0;
    virtual const YAML::Node& asset_paths() const = 0;
};
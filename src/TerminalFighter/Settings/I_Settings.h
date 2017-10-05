#pragma once

#include <yaml-cpp/yaml.h>

enum class SettingsSection : char {
    VIDEO_SETTINGS = 'V',
    ASSET_PATHS = 'A',
};

class I_Settings {
public:
    virtual bool reload_all_settings() = 0;
    virtual bool load_string(
        SettingsSection group,
        std::vector<std::string> keys,
        std::string& value) const = 0;
    virtual bool load_number(
        SettingsSection section,
        std::vector<std::string> keys,
        double& value) const = 0;
    virtual bool load_bool(
        SettingsSection section,
        std::vector<std::string> keys,
        bool& value) const = 0;
    virtual const YAML::Node& video_settings() const = 0;
    virtual const YAML::Node& asset_paths() const = 0;
};
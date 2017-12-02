#pragma once

#include <yaml-cpp/yaml.h>

enum class SettingsSection : char {
    VIDEO_SETTINGS = 'V',
    ASSET_PATHS = 'A',
    MAIN_MENU = 'M',
};

class I_Settings {
public:
    virtual bool reload_all_settings() = 0;

    // If load functions return false
    // value will be undefined
    virtual bool load_str(
        SettingsSection group,
        std::vector<std::string> keys,
        std::string& value) const = 0;
    virtual bool load_int(
        SettingsSection section,
        std::vector<std::string> keys,
        int& value) const = 0;
    virtual bool load_double(
        SettingsSection section,
        std::vector<std::string> keys,
        double& value) const = 0;
    virtual bool load_bool(
        SettingsSection section,
        std::vector<std::string> keys,
        bool& value) const = 0;
    virtual bool load_str_map(
        SettingsSection section,
        std::vector<std::string> keys,
        std::map<std::string, std::string>& value) const = 0;
};

#pragma once

#include "I_Settings.h"

class Settings : public I_Settings {

    struct SettingsGroup {
        SettingsGroup(SettingsSection section, std::string file)
            : group_(section)
            , file_(file)
        {};

        SettingsSection group_;
        std::string file_;
        YAML::Node node_;
    };

public:
    // Constructor parametrizes paths to config files for testability
    // In actual code, same files should be passed in everytime
    Settings(
        std::string video_settings_file,
        std::string asset_paths_file);
    bool reload_all_settings();
    bool load_str(
        SettingsSection section,
        std::vector<std::string> keys,
        std::string& value) const;
    bool load_int(
        SettingsSection section,
        std::vector<std::string> keys,
        int& value) const;
    bool load_double(
        SettingsSection section,
        std::vector<std::string> keys,
        double& value) const;
    bool load_bool(
        SettingsSection section,
        std::vector<std::string> keys,
        bool& value) const;
    bool load_str_map(
        SettingsSection section,
        std::vector<std::string> keys,
        std::map<std::string, std::string>& value) const;

private:
    int reload_setting(SettingsSection section);
    const SettingsGroup* section_to_group(SettingsSection section) const;
    SettingsGroup* section_to_group(SettingsSection section);
    YAML::Node load_node(SettingsSection section, std::vector<std::string> keys) const;
    SettingsGroup video_settings_;
    SettingsGroup asset_paths_;
};


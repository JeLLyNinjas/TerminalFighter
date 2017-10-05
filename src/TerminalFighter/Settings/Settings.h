#pragma once

#include <string>

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
    Settings(
        std::string video_settings_file,
        std::string asset_paths_file);
    bool reload_all_settings();
    bool load_string(
        SettingsSection section,
        std::vector<std::string> keys,
        std::string& value) const;
    bool load_number(
        SettingsSection section,
        std::vector<std::string> keys,
        double& value) const;
    bool load_bool(
        SettingsSection section,
        std::vector<std::string> keys,
        bool& value) const;
    const YAML::Node& video_settings() const;
    const YAML::Node& asset_paths() const;

private:
    int reload_setting(SettingsSection section);
    SettingsGroup* section_to_group(SettingsSection section);
    const SettingsGroup* section_to_group(SettingsSection section) const;
    YAML::Node load_node(SettingsSection section, std::vector<std::string> keys) const;
    SettingsGroup video_settings_;
    SettingsGroup asset_paths_;
};


#pragma once

#include <string>

#include "I_Settings.h"

class Settings : public I_Settings {

    struct Setting {
        Setting(SettingsGroup group, std::string file)
            : group_(group)
            , file_(file)
        {};

        SettingsGroup group_;
        std::string file_;
        YAML::Node node_;
    };

public:
    Settings(
        std::string video_settings_file,
        std::string asset_paths_file);
    bool reload_all_settings();
    bool load_string(
        SettingsGroup group,
        std::vector<std::string> keys,
        std::string& value) const;
    const YAML::Node& video_settings() const;
    const YAML::Node& asset_paths() const;

private:
    int reload_setting(SettingsGroup group);
    Setting* group_to_setting(SettingsGroup group);
    Setting video_settings_;
    Setting asset_paths_;
};
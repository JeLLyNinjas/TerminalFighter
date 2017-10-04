#pragma once

#include <string>

#include "I_Settings.h"

class Settings : public I_Settings {
public:
    Settings(
        std::string video_settings_file,
        std::string asset_paths_file);
    bool reload_settings();
    const YAML::Node& video_settings() const;
    const YAML::Node& asset_paths() const;

private:
    YAML::Node video_settings_;
    std::string video_settings_file_;

    YAML::Node asset_paths_;
    std::string asset_paths_file_;
};
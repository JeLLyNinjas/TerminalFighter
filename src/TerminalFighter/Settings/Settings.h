#pragma once

#include <string>

#include "I_Settings.h"

class Settings : public I_Settings {
public:
    Settings();
    bool reload_settings();
    const YAML::Node& video_settings() const;
    const YAML::Node& asset_paths() const;

private:
    YAML::Node video_settings_;
    YAML::Node asset_paths_;
};
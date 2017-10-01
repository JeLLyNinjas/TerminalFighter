#include <yaml-cpp/yaml.h>
#include <glog/logging.h>

#include "Settings.h"

namespace {
    const std::string VIDEO_SETTINGS_FILE = "config/video_settings.yml";
    const std::string ASSETS_PATHS_FILE = "config/asset_paths.yml";
}

Settings::Settings() {
}

// Used for initialization as well as forced reload of settings
bool Settings::reload_settings() {
    LOG(INFO) << "Reloading all settings";
    int errors = 0;

    try {
        video_settings_ = YAML::LoadFile(VIDEO_SETTINGS_FILE);
        LOG(INFO) << "Successfully loaded " << VIDEO_SETTINGS_FILE;
    } catch (YAML::BadFile) {
        LOG(ERROR) << "Failed to load file: " << VIDEO_SETTINGS_FILE;
        errors++;
    }

    try {
        asset_paths_ = YAML::LoadFile(ASSETS_PATHS_FILE);
        LOG(INFO) << "Successfully loaded " << ASSETS_PATHS_FILE;
    } catch (YAML::BadFile) {
        LOG(ERROR) << "Failed to load file: " << ASSETS_PATHS_FILE;
        errors++;
    }

    return !errors;
}

const YAML::Node& Settings::video_settings() const {
    return video_settings_;
}

const YAML::Node& Settings::asset_paths() const {
    return asset_paths_;
}

#include <yaml-cpp/yaml.h>
#include <glog/logging.h>

#include "Settings.h"

Settings::Settings(
    std::string video_settings_file,
    std::string asset_paths_file)
    : video_settings_file_(video_settings_file)
    , asset_paths_file_(asset_paths_file) {
}

// Used for initialization as well as forced reload of settings
bool Settings::reload_settings() {
    LOG(INFO) << "Reloading all settings";
    int errors = 0;

    try {
        video_settings_ = YAML::LoadFile(video_settings_file_);
        LOG(INFO) << "Successfully loaded " << video_settings_file_;
    } catch (YAML::BadFile) {
        LOG(ERROR) << "Failed to load file: " << video_settings_file_;
        errors++;
    }

    try {
        asset_paths_ = YAML::LoadFile(asset_paths_file_);
        LOG(INFO) << "Successfully loaded " << asset_paths_file_;
    } catch (YAML::BadFile) {
        LOG(ERROR) << "Failed to load file: " << asset_paths_file_;
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

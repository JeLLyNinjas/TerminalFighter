#include <yaml-cpp/yaml.h>
#include <glog/logging.h>

#include "Settings.h"

Settings::Settings(
    std::string video_settings_file,
    std::string asset_paths_file)
    : video_settings_(SettingsGroup::VIDEO_SETTINGS, video_settings_file)
    , asset_paths_(SettingsGroup::ASSET_PATHS, asset_paths_file) {
    if (!reload_all_settings()) {
        LOG(FATAL) << "Failed to initialize settings";
    }
}

// Used for initialization as well as forced reload of settings
bool Settings::reload_all_settings() {
    LOG(INFO) << "Reloading all settings";
    int errors = 0;

    errors += reload_setting(SettingsGroup::VIDEO_SETTINGS);
    errors += reload_setting(SettingsGroup::ASSET_PATHS);

    return !errors;
}

int Settings::reload_setting(SettingsGroup group) {
    Setting* setting = group_to_setting(group);

    try {
        setting->node_ = YAML::LoadFile(setting->file_);
    } catch (YAML::BadFile) {
        LOG(ERROR) << "Failed to load file: " << setting->file_;
        return 1;
    }

    LOG(INFO) << "Successfully loaded " << setting->file_;
    return 0;
}

Settings::Setting* Settings::group_to_setting(SettingsGroup group) {
    switch (group) {
        case SettingsGroup::VIDEO_SETTINGS:
            return &video_settings_;
            break;

        case SettingsGroup::ASSET_PATHS:
            return &asset_paths_;
            break;
    }

    LOG(FATAL) << "Attempted to load unknown settings group";

    // should never get here
    return &video_settings_;
}

bool Settings::load_string(
    SettingsGroup group,
    std::vector<std::string> keys,
    std::string& value) const {
    return false;
}

const YAML::Node& Settings::video_settings() const {
    return video_settings_.node_;
}

const YAML::Node& Settings::asset_paths() const {
    return asset_paths_.node_;
}

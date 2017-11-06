#include <glog/logging.h>

#include "Settings.h"

// Internal helper func
std::string vec_to_str(std::vector<std::string> vec) {
    std::string result = "{";

    for (auto str : vec) {
        result += str + ",";
    }

    return result += "}";
}

Settings::Settings(
    std::string video_settings_file,
    std::string asset_paths_file)
    : video_settings_(SettingsSection::VIDEO_SETTINGS, video_settings_file)
    , asset_paths_(SettingsSection::ASSET_PATHS, asset_paths_file) {
    if (!reload_all_settings()) {
        LOG(FATAL) << "Failed to initialize settings";
    }
}

// Used for initialization as well as forced reload of settings
bool Settings::reload_all_settings() {
    LOG(INFO) << "Reloading all settings";
    int errors = 0;

    errors += reload_setting(SettingsSection::VIDEO_SETTINGS);
    errors += reload_setting(SettingsSection::ASSET_PATHS);

    return !errors;
}

bool Settings::load_str(
    SettingsSection section,
    std::vector<std::string> keys,
    std::string& value) const {

    YAML::Node node = load_node(section, keys);

    if (!node.IsScalar()) {
        LOG(ERROR) << "SettingsGroup " << vec_to_str(keys)
                   << " from section " << static_cast<char>(section)
                   << " is not string";
        return false;
    }

    try {
        value = node.as<std::string>();
    } catch (YAML::InvalidNode e) {
        LOG(ERROR) << "Could not load setting " << vec_to_str(keys)
                   << " from section " << static_cast<char>(section)
                   << ", " << e.msg;
        return false;
    } catch (YAML::RepresentationException e) {
        LOG(ERROR) << "Couldn't load " << vec_to_str(keys) << " as string. " << e.msg;
        return false;
    }

    return true;
}

bool Settings::load_int(
    SettingsSection section,
    std::vector<std::string> keys,
    int& value) const {

    YAML::Node node = load_node(section, keys);

    if (!node.IsScalar()) {
        LOG(ERROR) << "SettingsGroup " << vec_to_str(keys)
                   << " from section " << static_cast<char>(section)
                   << " is not int";
        return false;
    }

    try {
        value = node.as<int>();
    } catch (YAML::InvalidNode e) {
        LOG(ERROR) << "Could not load setting " << vec_to_str(keys)
                   << " from section " << static_cast<char>(section)
                   << ", " << e.msg;
        return false;
    } catch (YAML::RepresentationException e) {
        LOG(ERROR) << "Couldn't load " << vec_to_str(keys) << " as int. " << e.msg;
        return false;
    }

    return true;
}

bool Settings::load_double(
    SettingsSection section,
    std::vector<std::string> keys,
    double& value) const {

    YAML::Node node = load_node(section, keys);

    if (!node.IsScalar()) {
        LOG(ERROR) << "SettingsGroup " << vec_to_str(keys)
                   << " from section " << static_cast<char>(section)
                   << " is not double";
        return false;
    }

    try {
        value = node.as<double>();
    } catch (YAML::InvalidNode e) {
        LOG(ERROR) << "Could not load setting " << vec_to_str(keys)
                   << " from section " << static_cast<char>(section)
                   << ", " << e.msg;
        return false;
    } catch (YAML::RepresentationException e) {
        LOG(ERROR) << "Couldn't load " << vec_to_str(keys) << " as double. " << e.msg;
        return false;
    }

    return true;
}

bool Settings::load_bool(
    SettingsSection section,
    std::vector<std::string> keys,
    bool& value) const {

    YAML::Node node = load_node(section, keys);

    if (!node.IsScalar()) {
        LOG(ERROR) << "SettingsGroup " << vec_to_str(keys)
                   << " from section " << static_cast<char>(section)
                   << " is not boolean";
        return false;
    }

    try {
        value = node.as<bool>();
    } catch (YAML::InvalidNode e) {
        LOG(ERROR) << "Could not load setting " << vec_to_str(keys)
                   << " from section " << static_cast<char>(section)
                   << ", " << e.msg;
        return false;
    } catch (YAML::RepresentationException e) {
        LOG(ERROR) << "Couldn't load " << vec_to_str(keys) << " as bool. " << e.msg;
        return false;
    }

    return true;
}

bool Settings::load_str_map(
    SettingsSection section,
    std::vector<std::string> keys,
    std::map<std::string, std::string>& value) const {

    YAML::Node node = load_node(section, keys);

    if (!node.IsMap()) {
        LOG(ERROR) << "SettingsGroup " << vec_to_str(keys)
                   << " from section " << static_cast<char>(section)
                   << " is not a map";
        return false;
    }

    value.clear();

    for (YAML::const_iterator it = node.begin(); it != node.end(); ++it) {
        try {
            value[it->first.as<std::string>()] = it->second.as<std::string>();
        } catch (YAML::InvalidNode e) {
            LOG(ERROR) << "Could not load setting " << vec_to_str(keys)
                       << " from section " << static_cast<char>(section)
                       << ", " << e.msg;
            return false;
        } catch (YAML::RepresentationException e) {
            LOG(ERROR) << "Couldn't load " << vec_to_str(keys) << " as map<str,str>. " << e.msg;
            return false;
        }
    }

    return true;
}

/* PRIVATE FUNCTIONS */

int Settings::reload_setting(SettingsSection section) {
    SettingsGroup* setting = section_to_group(section);

    try {
        setting->node_ = YAML::LoadFile(setting->file_);
    } catch (YAML::BadFile e) {
        LOG(ERROR) << "Failed to load file: " << setting->file_ << ", " << e.msg;
        return 1;
    }

    LOG(INFO) << "Successfully loaded " << setting->file_;
    return 0;
}

const Settings::SettingsGroup* Settings::section_to_group(SettingsSection section) const {
    switch (section) {
        case SettingsSection::VIDEO_SETTINGS:
            return &video_settings_;
            break;

        case SettingsSection::ASSET_PATHS:
            return &asset_paths_;
            break;
    }

    LOG(FATAL) << "Attempted to load unknown settings section" << static_cast<char>(section);

    // should never get here
    return &video_settings_;
}

Settings::SettingsGroup* Settings::section_to_group(SettingsSection section) {
    return const_cast<Settings::SettingsGroup*>(static_cast<const Settings*>(this)->section_to_group(section));
}

YAML::Node Settings::load_node(SettingsSection section, std::vector<std::string> keys) const {
    YAML::Node node = YAML::Clone(section_to_group(section)->node_);

    for (auto key : keys) {
        node = node[key];
    }

    return node;
}


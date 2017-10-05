#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/TerminalFighter/Settings/Settings.h"

namespace {
    std::string TEST_VIDEO_SETTINGS_FILE = "../config.example/video_settings.yml";
    std::string TEST_ASSET_PATHS_FILE = "../config.example/asset_paths.yml";
}

class SettingsTest : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

// Mostly testing example_config is actually loadable
TEST(SettingsTest, reload_settings) {
    Settings settings(
        TEST_VIDEO_SETTINGS_FILE,
        TEST_ASSET_PATHS_FILE);

    EXPECT_TRUE(settings.reload_all_settings());
}

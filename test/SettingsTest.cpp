#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/TerminalFighter/Settings/Settings.h"

namespace {
    // relative to build folder
    std::string VIDEO_SETTINGS_FILE = "../config.example/video_settings.yml";
    std::string ASSET_PATHS_FILE = "../config.example/asset_paths.yml";

    std::string TEST_CONFIG_FILE = "../test/test.yml";
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
        VIDEO_SETTINGS_FILE,
        ASSET_PATHS_FILE);

    EXPECT_TRUE(settings.reload_all_settings());
}

TEST(SettingsTest, load_string) {
    Settings settings(
        TEST_CONFIG_FILE,
        TEST_CONFIG_FILE);

    std::string actual;

    EXPECT_TRUE(settings.load_string(
                    SettingsSection::VIDEO_SETTINGS,
    {"level", "hello"},
    actual));

    EXPECT_EQ("world!", actual);
}
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/TerminalFighter/Settings/Settings.h"

using ::testing::ContainerEq;

namespace {
    // relative to build folder
    std::string VIDEO_SETTINGS_FILE = "../config.example/video_settings.yml";
    std::string ASSET_PATHS_FILE = "../config.example/asset_paths.yml";
    std::string MAIN_MENU_FILE = "../config.example/main_menu.yml";

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
        ASSET_PATHS_FILE,
        MAIN_MENU_FILE);

    EXPECT_TRUE(settings.reload_all_settings());
}

TEST(SettingsTest, load_base) {
    Settings settings(
        TEST_CONFIG_FILE,
        TEST_CONFIG_FILE,
        TEST_CONFIG_FILE);

    std::string actual;

    EXPECT_TRUE(settings.load_str(SettingsSection::VIDEO_SETTINGS, {"base"}, actual));

    EXPECT_EQ("acid", actual);
}


TEST(SettingsTest, load_string) {
    Settings settings(
        TEST_CONFIG_FILE,
        TEST_CONFIG_FILE,
        TEST_CONFIG_FILE);

    std::string actual;

    EXPECT_TRUE(settings.load_str(
                    SettingsSection::VIDEO_SETTINGS,
    {"level", "hello"},
    actual));

    EXPECT_EQ("world!", actual);
}

TEST(SettingsTest, load_integer) {
    Settings settings(
        TEST_CONFIG_FILE,
        TEST_CONFIG_FILE,
        TEST_CONFIG_FILE);

    int actual;

    EXPECT_TRUE(settings.load_int(
                    SettingsSection::VIDEO_SETTINGS,
    {"level", "integer"},
    actual));

    EXPECT_EQ(5, actual);
}

TEST(SettingsTest, load_decimal) {
    Settings settings(
        TEST_CONFIG_FILE,
        TEST_CONFIG_FILE,
        TEST_CONFIG_FILE);

    double actual;

    EXPECT_TRUE(settings.load_double(
                    SettingsSection::VIDEO_SETTINGS,
    {"level", "decimal"},
    actual));

    EXPECT_EQ(0.25, actual);
}

TEST(SettingsTest, load_boolean) {
    Settings settings(
        TEST_CONFIG_FILE,
        TEST_CONFIG_FILE,
        TEST_CONFIG_FILE);

    bool actual;

    EXPECT_TRUE(settings.load_bool(
                    SettingsSection::VIDEO_SETTINGS,
    {"level", "fact"},
    actual));

    EXPECT_EQ(true, actual);
}

TEST(SettingsTest, load_str_map) {
    Settings settings(
        TEST_CONFIG_FILE,
        TEST_CONFIG_FILE,
        TEST_CONFIG_FILE);

    std::map<std::string, std::string> actual;

    std::map<std::string, std::string> expected = {
        {"boy", "A young male persons"},
        {"girl", "A young female persons"}
    };

    EXPECT_TRUE(settings.load_str_map(
                    SettingsSection::VIDEO_SETTINGS,
    {"level", "dictionary"}, actual));

    EXPECT_THAT(actual, ContainerEq(expected));
}

TEST(SettingsTest, load_bad_key) {
    Settings settings(
        TEST_CONFIG_FILE,
        TEST_CONFIG_FILE,
        TEST_CONFIG_FILE);

    std::string actual;

    EXPECT_FALSE(settings.load_str(
                     SettingsSection::VIDEO_SETTINGS,
    {"level", "doesnt_exit"},
    actual));
}

TEST(SettingsTest, load_bad_convert) {
    Settings settings(
        TEST_CONFIG_FILE,
        TEST_CONFIG_FILE,
        TEST_CONFIG_FILE);

    double actual;

    EXPECT_FALSE(settings.load_double(
                     SettingsSection::VIDEO_SETTINGS,
    {"level", "hello"},
    actual));
}

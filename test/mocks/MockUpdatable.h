#pragma once

#include "gmock/gmock.h"

#include "../../src/Engine/GameObject/I_Updatable.h"

class MockUpdatable : public I_Updatable {
public:
    MockUpdatable() {}

    MOCK_METHOD0(update, void());
};

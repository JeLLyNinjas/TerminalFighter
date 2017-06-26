#pragma once

#include "gmock/gmock.h"

#include "../../src/I_Updatable.h"

class MockUpdatable : public I_Updatable {
public:
    MockUpdatable() {}

    MOCK_METHOD0(update, void());
};

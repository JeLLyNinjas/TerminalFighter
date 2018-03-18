#pragma once

#include "gmock/gmock.h"

#include "../../src/Engine/Hitbox/I_Hitbox.h"
#include "../../src/Engine/JN_Rect/JN_Rect.h"

class MockHitbox : public I_Hitbox {
public:
    MockHitbox() {}

    MOCK_CONST_METHOD1(is_overlapping, bool(const I_Hitbox&));
    MOCK_METHOD2(set_pos, void(double, double));
    MOCK_CONST_METHOD0(hitbox, const JN_Rect & ());
    MOCK_CONST_METHOD0(hitbox_circle, const Circle & ());
    MOCK_CONST_METHOD0(hitbox_type, const Shape::Shape & ());
};

#pragma once

#include "gmock/gmock.h"

#include "GameObject.h"

class GraphicsHandler;

class MockGameObject : public GameObject {
public:
    MockGameObject() {}

    MOCK_METHOD0(update, void());
    MOCK_METHOD1(draw, void(GraphicsHandler& graphics));
    MOCK_CONST_METHOD0(hitbox, const Hitbox & ());
    MOCK_METHOD1(notify_collision, void(GameObject&));
};

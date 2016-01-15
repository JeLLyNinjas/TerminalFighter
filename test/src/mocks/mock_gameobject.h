#pragma once 
#include "gmock/gmock.h"

#include "game_object.h"

class GraphicsHandler;

class MockGameObject : public GameObject {
public:
	MockGameObject() 
		: GameObject(0, 0) 
	{}

	MOCK_METHOD0(update, void());
	MOCK_METHOD1(draw, void(GraphicsHandler* graphics));	
};
#include "gmock/gmock.h"

#include "I_GameObjectMediator.h"

class MockGameObjectMediator : public I_GameObjectMediator {
public:
    MOCK_METHOD2(add_game_object, void(Team::Team, std::unique_ptr<GameObject>));
    MOCK_METHOD2(add_projectile, void(Team::Team, std::unique_ptr<GameObject>));
};

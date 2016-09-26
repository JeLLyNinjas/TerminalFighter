#include "gmock/gmock.h"

#include "I_GameObjectMediator.h"

class MockGameObjectMediator : public I_GameObjectMediator {
public:
    /* Proxy for non-copyable parameters http://kechengpuzi.com/q/s7616475 */
    virtual void add_game_object(Team::Team team, std::unique_ptr<GameObject> uPtr) {
        add_game_object_proxy(team, uPtr.get());
    }

    virtual void add_projectile(Team::Team team, std::unique_ptr<GameObject> uPtr) {
        add_game_object_proxy(team, uPtr.get());
    }

    MOCK_METHOD2(add_game_object_proxy, void(Team::Team, GameObject*));
    MOCK_METHOD2(add_projectile_proxy, void(Team::Team, GameObject*));
};

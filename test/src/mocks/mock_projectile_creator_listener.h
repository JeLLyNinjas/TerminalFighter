#include "gmock/gmock.h"

#include "game_constants.h"
#include "projectile_creator_listener.h"

class MockProjectileCreatorListener : public ProjectileCreatorListener {
public:
    MOCK_METHOD2(notify_projectile_launched, void(Projectile* projectile, Team::Team team));
};

#include "gmock/gmock.h"

#include "projectile_creator_listener.h"

class MockProjectileCreatorListener : public ProjectileCreatorListener {
public:
    MOCK_METHOD1(notify_projectile_launched, void(Projectile* projectile));
};
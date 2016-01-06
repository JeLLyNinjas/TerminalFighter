#include "gmock/gmock.h"
#include "missile_launcher_listener.h"

class MockMissileLauncherListener : public MissileLauncherListener {
public:
	MOCK_METHOD1(notify_missile_launched, void(Missile* missile));
};
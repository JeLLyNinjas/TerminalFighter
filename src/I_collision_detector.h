#pragma once 

class I_CollisionDetector {

public:	
	virtual void notifySensorCollisions() = 0;
	virtual void notifyProjectileCollisions() = 0;
	virtual void notifyShipCollisions() = 0;

};
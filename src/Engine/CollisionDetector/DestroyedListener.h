#pragma once

class DestroyedListener {
public:
    virtual ~DestroyedListener() {}
    virtual void object_destroyed(int id) = 0;
};

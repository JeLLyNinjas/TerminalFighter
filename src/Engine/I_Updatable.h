#pragma once

class I_Updatable {
public:
    virtual ~I_Updatable() {}
    virtual void update() = 0;
};

#pragma once
#include <vector>

template <class T>
class Observable {
public:
    void add_listener(T *listener) {
        listeners.push_back(listener);
    }

protected:
    std::vector<T *> listeners;
};

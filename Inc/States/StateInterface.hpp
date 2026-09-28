#pragma once

class StateInterface {
public:
    virtual ~StateInterface() = default; 
    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual void update() = 0;
};

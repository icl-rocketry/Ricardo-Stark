#pragma once
// Backwards Euler integrator

template <typename T>
class Integrator{

    public:

    Integrator(){};

    void integrate(T err, T dt)
    {      
        I += err * dt;
    }

    T getI(){return I;}

    private:
        
        T I = 0;

};

